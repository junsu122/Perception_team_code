import asyncio
import threading
import time
import tkinter as tk
from datetime import datetime

# 8/31 최신화
# ======================== 사용자 설정 ==========================

CYCLE_START = datetime.strptime("2025-08-10 12:28:20", "%Y-%m-%d %H:%M:%S")

timer_configs = {
    2: {"initial": ("빨강", 2), "cycle": [("초록", 32), ("주황", 3), ("빨강", 65)]},
    3: {"initial": ("빨강", 2), "cycle": [("초록", 32), ("주황", 3), ("빨강", 65)]},
    5: {"initial": ("빨강", 2), "cycle": [("초록", 47), ("주황", 3), ("빨강", 50)]},
    8: {"initial": ("빨강", 0), "cycle": [("초록", 27), ("주황", 3), ("빨강", 70)]},
    10: {"initial": ("빨강",0), "cycle": [("초록", 24), ("주황", 3), ("빨강", 73)]},
    11: {"initial": ("빨강",2), "cycle": [("초록", 37), ("주황", 3), ("빨강", 60)]}
}

TEXT_COLOR = {
    "초록": "green",
    "주황": "orange",
    "빨강": "red",
}

# ======================== 유틸/상태 계산 ==========================

def get_elapsed_seconds():
    return (datetime.now() - CYCLE_START).total_seconds()

def compute_initial_state(states, elapsed_time):
    """현재 사이클 내 위치를 계산해 (state, remaining, next, next2, index)를 반환"""
    cycle_length = sum(d for _, d in states)
    time_in_cycle = elapsed_time % cycle_length

    cumulative = 0
    for i, (state, duration) in enumerate(states):
        if cumulative + duration > time_in_cycle:
            remaining = (cumulative + duration) - time_in_cycle
            next_state = states[(i + 1) % len(states)][0]
            next2_state = states[(i + 2) % len(states)][0]
            return state, remaining, next_state, next2_state, i
        cumulative += duration
    # 이론상 도달하지 않지만 안전망
    return states[0][0], states[0][1], states[1][0], states[2][0], 0

# ======================== 초기 상태 세팅 ==========================

current_status = {}
elapsed_global = get_elapsed_seconds()

for timer_id, config in timer_configs.items():
    states = config["cycle"]
    initial_state, initial_duration = config.get("initial", ("대기", 0))

    if elapsed_global < initial_duration:
        current_status[timer_id] = {
            "state": initial_state,
            "remaining": initial_duration - elapsed_global,
            "next": states[0][0],
            "next2": states[1][0]
        }
    else:
        elapsed_for_cycle = elapsed_global - initial_duration
        state, remaining, next_state, next2_state, _ = compute_initial_state(states, elapsed_for_cycle)
        current_status[timer_id] = {
            "state": state,
            "remaining": remaining,
            "next": next_state,
            "next2": next2_state
        }

# ======================== 콘솔 상태 출력 ==========================

def print_timer_status():
    now_elapsed = get_elapsed_seconds()
    print(f"\n🕒 현재 시간: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
    print(f"⏱ 기준 시간: {CYCLE_START} | 경과 시간: {now_elapsed:.2f}초\n")
    for timer_id, info in sorted(current_status.items()):
        print(
            f"[타이머 {timer_id}] 상태: {info['state']} | 남은 시간: {info['remaining']:.2f}초 "
            f"| 다음: {info['next']} | 다다음: {info['next2']}"
        )

# ======================== GUI ==========================

class TimerDashboard(tk.Frame):
    def __init__(self, root):
        super().__init__(root)
        self.root = root
        self.pack(expand=True, fill="both")
        self.canvas = tk.Canvas(self, bg="white")
        self.canvas.pack(expand=True, fill="both")

        self.labels = {}
        self.columns = ["타이머", "현재 상태", "다음 상태", "다다음 상태", "남은 시간"]
        self.timer_ids = sorted(current_status.keys())
        self.cell_width = 130
        self.cell_height = 40

        self.draw_headers()
        self.update_ui()

    def draw_headers(self):
        for col_index, col_name in enumerate(self.columns):
            x = col_index * self.cell_width
            self.canvas.create_rectangle(x, 0, x + self.cell_width, self.cell_height, fill="#eee")
            self.canvas.create_text(
                x + self.cell_width // 2, self.cell_height // 2,
                text=col_name, font=("Arial", 12, "bold")
            )

    def update_ui(self):
        for row_index, timer_id in enumerate(self.timer_ids):
            info = current_status[timer_id]
            values = [
                str(timer_id),
                info["state"],
                info["next"],
                info["next2"],
                f"{info['remaining']:.2f} 초"
            ]
            for col_index, value in enumerate(values):
                key = (row_index, col_index)
                x1 = col_index * self.cell_width
                y1 = (row_index + 1) * self.cell_height
                x2 = x1 + self.cell_width
                y2 = y1 + self.cell_height

                bg_color = "#FFF3BF" if col_index == 1 else "white"
                # 상태 칸(1,2,3)만 색상을 적용. 숫자 칸(0,4)은 검정.
                fg_color = TEXT_COLOR.get(value, "black") if col_index in (1, 2, 3) else "black"

                if key not in self.labels:
                    self.canvas.create_rectangle(x1, y1, x2, y2, fill=bg_color, outline="gray")
                    label = tk.Label(self.canvas, text=value, bg=bg_color, fg=fg_color, font=("Arial", 11))
                    self.labels[key] = label
                    self.canvas.create_window(
                        x1 + self.cell_width // 2, y1 + self.cell_height // 2, window=label
                    )
                else:
                    label = self.labels[key]
                    label.config(text=value, bg=bg_color, fg=fg_color)

        self.root.after(200, self.update_ui)

# ======================== 타이머 루프 (동기화된) ==========================

async def run_timer(timer_id, config):
    initial_state, initial_duration = config.get("initial", ("대기", 0))
    states = config["cycle"]
    start_offset = get_elapsed_seconds()

    if start_offset < initial_duration:
        # 초기 구간(예: 빨강) 남은 시간부터 대기
        remaining = initial_duration - start_offset
        current_status[timer_id].update({
            "state": initial_state,
            "remaining": remaining,
            "next": states[0][0],
            "next2": states[1][0]
        })
        start_time = time.time()
        while time.time() - start_time < remaining:
            current_status[timer_id]["remaining"] = remaining - (time.time() - start_time)
            await asyncio.sleep(0.05)
        start_idx = 0  # 초기 구간 끝나면 사이클 처음부터
    else:
        # 사이클 중간 진입: 현재 상태의 '남은 시간'부터 먼저 소진
        elapsed_cycle = start_offset - initial_duration
        state, remaining, next_state, next2_state, idx = compute_initial_state(states, elapsed_cycle)
        current_status[timer_id].update({
            "state": state,
            "remaining": remaining,
            "next": next_state,
            "next2": next2_state
        })
        start_time = time.time()
        while time.time() - start_time < remaining:
            current_status[timer_id]["remaining"] = remaining - (time.time() - start_time)
            await asyncio.sleep(0.05)
        start_idx = (idx + 1) % len(states)  # 다음 상태부터 본격 루프

    # 이후엔 올바른 위치에서 계속 순환
    while True:
        for step in range(len(states)):
            i = (start_idx + step) % len(states)
            state, duration = states[i]
            current_status[timer_id].update({
                "state": state,
                "remaining": duration,
                "next": states[(i + 1) % len(states)][0],
                "next2": states[(i + 2) % len(states)][0],
            })
            start_time = time.time()
            while time.time() - start_time < duration:
                current_status[timer_id]["remaining"] = duration - (time.time() - start_time)
                await asyncio.sleep(0.05)
        start_idx = 0  # 다음 루프부터는 0부터

# ======================== 메인 루프 ==========================

async def main_async():
    elapsed_global = get_elapsed_seconds()
    if elapsed_global < 0:
        print(f"사이클 시작 전입니다. {abs(elapsed_global):.1f}초 후 시작됩니다.")
        await asyncio.sleep(abs(elapsed_global))

    tasks = [
        asyncio.create_task(run_timer(timer_id, config))
        for timer_id, config in timer_configs.items()
    ]
    await asyncio.gather(*tasks)

def start_async_loop():
    loop = asyncio.new_event_loop()
    asyncio.set_event_loop(loop)
    loop.run_until_complete(main_async())

# ======================== 실행 ==========================

if __name__ == "__main__":
    print_timer_status()  # 현재 상태 콘솔 출력
    root = tk.Tk()
    root.title("타이머 대시보드 (절대시간 동기화)")
    app = TimerDashboard(root)
    threading.Thread(target=start_async_loop, daemon=True).start()
    root.mainloop()

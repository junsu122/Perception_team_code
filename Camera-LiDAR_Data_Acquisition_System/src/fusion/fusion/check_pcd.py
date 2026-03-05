import open3d as o3d
import numpy as np

def load_and_visualize_pcd(filename):
    # PCD 파일 로드
    cloud = o3d.io.read_point_cloud(filename)

    if not cloud.has_points():
        print(f"❌ PCD 파일에 점이 없습니다: {filename}")
        return

    # PCD 파일의 기본 정보 출력
    print(f"✅ PCD 파일 로드 완료: {filename}")
    print(f"📌 총 점 개수: {len(cloud.points)}")

    # 좌표 범위 출력
    points = np.asarray(cloud.points)
    print(f"🔹 X 범위: {points[:, 0].min()} ~ {points[:, 0].max()}")
    print(f"🔹 Y 범위: {points[:, 1].min()} ~ {points[:, 1].max()}")
    print(f"🔹 Z 범위: {points[:, 2].min()} ~ {points[:, 2].max()}")

    # PCD 데이터 시각화
    o3d.visualization.draw_geometries([cloud], window_name="PCD Viewer")

if __name__ == "__main__":
    filename = "/home/junsu/1.cam/src/fusion/fusion/output_1739508739.pcd"  # 확인할 PCD 파일 이름 입력
    load_and_visualize_pcd(filename)

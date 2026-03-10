# 🚀 Perception Team Code Base

* 본 저장소는 **YOLO 기반 객체 인식 및 Camera-LiDAR 센서 퓨전**을 통한 자율주행 인지 알고리즘 프로젝트입니다.
* 각각은 패키지 형태로 사용한 그대로를 가져온것이며, 일부는 코드만 존재합니다.

---

## 🛠 주요 기능 (Key Features)

### 1. Object Detection & Segmentation
* **YOLO Series:** Bounding Box 탐지 및 Instance Segmentation 구현
* **Traffic System:** 신호등(Traffic Light) 및 표지판(Traffic Sign) 인식 로직
* **Tracking:** 콘 트래킹(Cone Tracking) 알고리즘

### 2. Sensor Data Processing
* **Data Acquisition:** Cam (logitech) 및 LiDAR 데이터 실시간 캡처
* **Camera Pre-processing:** 카메라 이미지 왜곡 보정 및 전처리
* **LiDAR Post-processing:**
  * `Crop`: ROI(관심 영역) 설정
  * `Cluster`: 객체 군집화 (Clustering)
  * `Line Erase`: 바닥면 제거 및 노이즈 필터링

### 3. Sensor Fusion
* **Fusion Logic:** 카메라-라이다 데이터 융합 및 보정
* **Validation:** 퓨전 결과 정합성 체크용 유틸리티

---

## ⚠️ 주의 사항 (Usage Warnings)

> [!CAUTION]
> * **단독 실행 주의:** 본 코드는 특정 시스템 환경에 의존적이므로 단독 실행 시 에러가 발생할 확률이 높습니다.
> * **노드 연결 필수:** ROS 환경 등의 노드 기반 통신 연결이 필요합니다.
> * **데이터 보안:** 데이터셋 및 원천 데이터 파일은 포함되어 있지 않습니다.
> * **버전 대응:** 라이브러리 및 종속성 버전에 따른 코드 수정이 필요할 수 있습니다.

---

## 💻 개발 환경 (Environment)(Ubuntu 22.04)
* **Languages:** `C++`, `Python`
* **Hardware:** Manta Camera, 3D LiDAR System(Velodyne), USB Cam(logitech)
* **Key Frameworks:** OpenCV, YOLO, Vimba SDK

---

## 수정중..

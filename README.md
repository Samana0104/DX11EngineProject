# DX11EngineProject

DirectX 11 기반 자체 3D 게임 엔진(`DX11GameEngine`)과 이를 활용해 제작한 ***Untitled Goose Game* 모작 3D 게임** 프로젝트입니다.

- **개발 기간**: `2024.11.04 ~ 2025.01.07`
- **개발 형태**: 3인 팀 프로젝트 (엔진 & UI / 맵 & 쉐이더 / 캐릭터 & AI)
- **개발 환경**: C++20, Visual Studio 2022 (`x64`), DirectX 11, HLSL (Shader Model 5.0)

---

## 주요 기능

### 1. 자체 3D 게임 엔진 (`DX11GameEngine`)
- **멀티 렌더 타겟 파이프라인**: `MAIN`, `GUI`, `SHADOW`, `SUB1`, `SUB2` 렌더 타겟 분리 및 합성(`MergeRenderTarget`), `EasyRender` 래퍼 제공
- **그래픽스 & 쉐이더**:
  - Blinn-Phong 조명, 카툰(Toon) 셰이딩, 실루엣 외곽선(Edge), 큐브맵 환경 매핑(`CartoonEnvPS.hlsl`)
  - 본 스키닝 애니메이션 버텍스 쉐이더(`BasicAniVS.hlsl`), 노멀 시각화 지오메트리 쉐이더(`NormalGS.hlsl`), 스카이박스 큐브맵(`CubeMapObj`)
- **지형 & 공간 분할 최적화**: 하이트맵(`HeightMap`) 기반 3D 지형 렌더링, 쿼드트리(`QuadTree`) 공간 분할 및 절두체 컬링(`Frustum`)
- **리소스 & 에셋 관리**: 팩토리 패턴 기반 중앙 리소스 매니저(`AssetsMgr`), 엔진 전용 바이너리 포맷 로더(`HBSLoader`, `SkmLoader`), 폴더 자동 로딩(`HBSAutoLoader`)
- **UI & 텍스트**: Direct2D / DirectWrite 기반 폰트 렌더링, 슬라이드 애니메이션 퀘스트 UI(`QuestGUI`), 로비/인게임 버튼 UI
- **시스템 & 디버그**: AABB 기반 충돌 컴포넌트(`CollisionComponent`), 옵저버 패턴 이벤트 시스템(`EventHandler`), 씬 매니저(`SceneMgr`), FMOD 오디오(`HSound`), 디버그용 Dear ImGui 연동 및 스크린샷 저장

### 2. FBX 에셋 컨버터 (`FbxConverter`)
- Autodesk FBX SDK를 사용해 `.fbx` 파일에서 메시/서브메시, 머티리얼, 본 계층 및 스키닝 가중치, 키프레임 애니메이션 데이터를 추출
- 런타임 로딩 속도와 구조를 최적화하기 위해 엔진 전용 바이너리 포맷으로 변환 및 익스포트:
  - `.hbs`: 메시, 서브메시, 본 구조 및 충돌 범위 데이터
  - `.skm`: 본 키프레임 스키닝 애니메이션 클립

### 3. 게임플레이 (`Client`)
- **플레이어 캐릭터 (`Goose`)**:
  - 걷기, 달리기, 웅크리기, 날갯짓, 울기 등 11종의 스키닝 애니메이션 상태 전환
  - 부리 본(`beaklower`) 소켓 부착을 통해 당근, 호박 등 동적 3D 오브젝트를 물고 옮기는 상호작용 구현
  - 이동 속도 및 행동에 따른 발소리, 울음소리, 잡기 효과음 재생
- **NPC AI (`Gardener`)**:
  - FSM 상태 머신(`Idle`, `Chasing`, `Pushing`) 기반 행동 제어
  - 161×161 그리드 맵 위에서 **A\* 경로 탐색(`Astar`)** 알고리즘을 통해 장애물을 회피하며 순찰 및 거위 추적
- **퀘스트 & 씬 구성**:
  - 로비(`SceneLobby`) 및 인게임(`SceneGame`) 씬 전환
  - 피크닉 돗자리(`PicnicRug`)에 당근과 호박을 가져오는 퀘스트 진행 및 클리어 연출

### 4. 네트워크 라이브러리 (`NetworkLib`)
- Windows IOCP와 워커 스레드 풀을 활용한 비동기 서버(`NetIOCPServ`), 세션 관리(`SessionManager`), 클라이언트(`NetClient`), 패킷 구조(`Packet`) 및 테스트 프로젝트 포함

---

## 프로젝트 구조

```text
DX11EngineProject/
├── Engine.sln              # Visual Studio 2022 솔루션
├── engine/                 # DX11GameEngine (정적 라이브러리)
│   ├── Ai/                 # A* 경로 탐색
│   ├── Asset/              # 리소스 매니저, 팩토리, .hbs/.skm 로더, 메시/쉐이더/텍스처/폰트/사운드
│   ├── Core/               # 엔진 코어, D3D11 디바이스, 윈도우, 이벤트 핸들러
│   ├── DesignPattern/      # 싱글톤, 옵저버 패턴
│   ├── Gui/                # 버튼 및 퀘스트 UI
│   ├── Input/              # 키보드/마우스 입력 처리
│   ├── Object/             # 2D/3D 오브젝트, 카메라, 절두체, 쿼드트리, 충돌, EasyRender
│   ├── Scene/              # 씬 인터페이스 및 씬 매니저
│   └── Timer/              # 프레임 타이머
├── Client/                 # Untitled Goose Game 모작 클라이언트
│   ├── Object/             # Goose, Gardener(AI), Static/Dynamic 3D 오브젝트, 타이틀 UI
│   ├── SceneLobby.*        # 로비 씬
│   └── SceneGame.*         # 인게임 씬
├── FbxConverter/           # FBX → .hbs / .skm 변환 툴
├── network/                # Windows IOCP 기반 네트워크 라이브러리 및 테스트
└── res/                    # 쉐이더(.hlsl), 메시(.hbs), 애니메이션(.skm), 텍스처, 하이트맵, 사운드
```

---

## 조작법

| 키 | 동작 |
| :--- | :--- |
| `↑` `↓` `←` `→` | 이동 (8방향) |
| `Shift` | 달리기 |
| `Ctrl` | 고개 숙이기 / 웅크리기 |
| `X` | 날갯짓 |
| `Space` | 울기 (Honk) |
| `Z` | 오브젝트 물기 / 놓기 |
| `Tab` | 퀘스트 목록 열기 / 닫기 |
| `ESC` | 일시정지 메뉴 |
| `Home` | 스크린샷 저장 |

---

## 기술 스택 & 외부 라이브러리

- **Language & IDE**: C++20, Visual Studio 2022
- **Graphics & Audio**: DirectX 11, Direct2D, DirectWrite, HLSL 5.0, FMOD
- **Libraries**: DirectXTK, GLM, Dear ImGui (Debug), Autodesk FBX SDK (`FbxConverter`)

---

## 빌드 방법

1. [외부 라이브러리](https://mega.nz/file/T7olzAha#GCdIo0FPBEpdE4AF9ckVkFaiVmZkEgZEaSqsbLu1a3s)를 다운로드하여 솔루션 루트의 `extern/` 경로에 배치합니다.
2. Visual Studio 2022에서 `Engine.sln`을 엽니다.
3. 플랫폼을 `x64` (`Debug` 또는 `Release`)로 선택한 뒤, `DX11GameEngine` → `Client` 순서로 빌드합니다.

---

## 참고 문서

- [엔진 튜토리얼](https://relic-telephone-6f4.notion.site/Engine-tutorials-49ed0bc0ec4d4161bb6c6c40c3005bdb?pvs=4)
- [코드 컨벤션](https://relic-telephone-6f4.notion.site/Code-convention-0ef00703de4f4184aa1d2df4bca91f43?pvs=4)
- [기획안](https://relic-telephone-6f4.notion.site/13eb0ebae73380389afce304653c47f7?v=13eb0ebae73381daa08d000c1a59e85e&pvs=4)
- [회의록](https://relic-telephone-6f4.notion.site/d842a090d544440187e529face827646?v=aa4bb530ae3a4e68a81f145a3a83e985&pvs=4)

## 23-2 Ewha Womans University "Computer Graphics"

### learnopengl.com code repository

Contains code samples for all chapters of Learn OpenGL and [https://learnopengl.com](https://learnopengl.com).

---
### ✏️소개
**1.RobotArm**

   **1. Display_RobotArm**
      
    - RobotArm, Teapot(img), Wood 바닥(img) 구현
    - 키보드 클릭 후 왼쪽 마우스 드래그로 RobotArm 이동
       1 클릭 -> 왼쪽 마우스로 전체 RobotArm을 이동
       2 클릭 -> 왼쪽 마우스로 RobotArm 방향을 좌우로 이동
       3 클릭 -> 왼쪽 마우스로 RobotArm 방향을 위아래로 이동
       4 클릭 -> 왼쪽 마우스로 RobotArm 머리 부분 움직이기
       5 클릭 -> 왼쪽 마우스로 RobotArm 집게 부분 움직이기

   **2. Camera_Interface**

    - 오른쪽 마우스 드래그로 카메라가 보는 방향 이동
    - W, S, A, D 키로 카메라 위치를 상하좌우로 이동
    

   **3. Render_Own_Model**

    - Teapot model 대신 Zephyr 사용

   **4. PointLight_and_SpotLight**

    - Blinn-Phong illumination을 이용한 radial and angular attenuation 구현
    - L키 클릭 -> angular attenuation   

**2.Simple_Raytracer**
   **1. Raytracing**

    - 구 외에 다른 물체(정육면체) 구현
    - light source 정의
    - ambient, diffuse 구현, specular 구현 x
---
### 🖱️빌드 방법
1. Cmake 설치
2. 코드 Clone 또는 Zip 파일 다운 후 압축 풀기
3. 다운받은 폴더 안에 build 폴더 생성
4. Cmake gui 사용
   - Where is the source code: 폴더명
   - Where is the build code: 폴더/build
5. Configure -> Generate
6. build 폴더에 들어가서 sln 파일 실행
7. 원하는 파일 시작프로젝트로 설정
8. 실행

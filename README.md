> [!NOTE]
> **Họ và tên**: Nguyễn Văn Hoàng<br/>
> **MSSV**: 23020667<br/>
> **LHP**: INT2215 52<br/>
> **Tên dự án**: *IQ chess* (cờ IQ)<br/>

# Mục Lục

- [Mục Lục](#mục-lục)
- [Chủ đề](#chủ-đề)
- [Tự đánh giá](#tự-đánh-giá)
  - [Phát triển 🧑‍💻](#phát-triển-)
  - [Các chức năng](#các-chức-năng)
    - [Màn hình chính](#màn-hình-chính)
    - [Play](#play)
    - [Instruction](#instruction)
    - [Exit](#exit)
  - [Một số điểm nổi bật về giao diện và trải nghiệm khi chơi](#một-số-điểm-nổi-bật-về-giao-diện-và-trải-nghiệm-khi-chơi)
    - [Bàn cờ và quân cơ](#bàn-cờ-và-quân-cơ)
    - [Hiệu ứng âm thanh](#hiệu-ứng-âm-thanh)
- [Phân tích sơ bộ về code](#phân-tích-sơ-bộ-về-code)
    - [Các hàm chính](#các-hàm-chính)
- [Demo](#demo)


# Chủ đề 

Bàn cờ như một câu đố thử thách IQ của bạn, nếu bạn có thể giải nó bạn đã là số ít những người có tư duy và tính kiên nhẫn vượt trội.

# Tự đánh giá

Em tự đánh giá game của mình không phải một con game dành cho đa số mọi người, nó không đơn thuần là một con game giải trí mà còn thử thách trí tuệ người chơi, chỉ những người thực sự có trí tuệ và lòng kiên trì mới có hứng thú và giải được trò chơi.

Độ phức tạp của trò chơi không cao và code cũng khá đơn giản nhưng yếu tố độc lạ và có thể nói nó chưa từng xuất hiện trước đây và trùng với một mô típ game nào - em cho rằng đó là một điểm cộng và cũng là sự khác biệt của mình.

## Phát triển 🧑‍💻

Bắt đầu vào ngày *10/03/2024*, dự án được em phát triển dựa trên niềm yêu thích với các trò chơi liên quan đến cờ và yêu cầu học tập của môn học. Vốn là người sẵn có sự yêu thích và niềm đam mê đặc biệt các trò chơi cờ như: cờ vây, cờ caro, đặc biệt là cờ tướng...

Em đã lên ý tưởng cho game của mình sẽ là một trò chơi cờ tư duy, với các tiêu chí đặt ra rằng trò chơi vẫn phải đảm bảo được tính thú vị, thử thách trí tuệ và luật chơi phải càng đơn giản càng tốt để thuận tiện cho việc chuyển hóa trò chơi đó từ ý tưởng thành những dòng code, hơn thế nữa đó phải là một trò chơi đảm bảo tính mới, sáng tạo, độc quyền và chưa bị trùng lặp với những con game đã tồn tại trên mạng, em đã chọn lựa và sàng lọc ra con game này với tên gọi **IQ CHESS**, nguồn gốc trò chơi này là một loại cờ được Gia Cát Lượng sáng tạo ra trong thời Tam Quốc để giúp quân lính rèn luyện trí tuệ và cũng là để chọn ra những chiến bình ưu tú và toàn diện nhất, tên quốc tế của nó là **KONGMINH CHESS** Việt hóa là cờ Khổng Minh. 

Dựa trên ý tưởng đó em đã có những dòng code đầu tiên cho con game của mình, dần dần bàn cờ, quân cờ, luật chơi và các tính năng khác dần được hình thành.

## Hướng dẫn cài đặt

Download file nén của game tại [đây](https://github.com/Hoangyd/IQchesss/releases/download/v1/IQchesss.zip), giải nén file `IQchesss.zip` và chạy file `main.exe` để chơi game.

## Các chức năng

### Màn hình chính

<img src="image\manhinhchinh.png" alt="manhinhchinh.png" style="zoom:50%;" />

Màn hình chính gồm tiêu đề, và các nút điều hướng sau:

* **Start**: bắt đầu chơi.
* **Instruction**: hướng dẫn choi.
* **Exit**: Thoát game.

### Play

<img src="image\playbutton.png" alt="playbutton.png" style="zoom:20%;" />

Trong khi chơi, các thông số được hiện là **số cờ còn lại, thời gian chơi**. Ngoài ra để đảm bảo rằng người chơi dù căng não những vẫn cảm nhận được sự thoải mái, phiêu trong từng nước cờ, chạy dưới nền sẽ là một đoạn nhạc cực chill duy trì sự thoải mái và nâng cao độ tập trung.

Phía bên phải góc dưới có nút reset bà cờ để chuyển bàn cờ về bàn cờ ban đầu lúc bạn bắt đầu chơi.

<img src="image\againbutton.png" alt="againbutton.png" style="zoom:20%;" />

### Instruction 

<img src="image\infobtn.png" alt="infobtn.png" style="zoom:20%;" />

Nếu bạn vẫn chưa hiểu luật chơi thì đây chính là cứu tinh của bạn, luật chơi, cách đi cờ cho hợp lệ, điều kiện thắng thua, tất cả đều được viết rất cụ thể và rõ ràng.

### Exit

<img src="image\exitbutton.png" alt="exitbutton.png" style="zoom:20%;" />

Đây là nút dùng để thoát game, bạn hãy sử dụng nó nếu cảm thấy mất kiên nhẫn và không thể tiếp tục cuộc chơi.

## Một số điểm nổi bật về giao diện và trải nghiệm khi chơi

### Bàn cờ và quân cơ 

Với màu sắc, độ sắc nét tinh sảo và hoàn mĩ của hình ảnh bàn cờ và quân cờ được tự thiết kế và chỉnh sủa hoàn toàn mang đến cho người một cảm giác rất chuyên nghiệp trên từng nước cờ.

### Hiệu ứng âm thanh 

Đi kèm với nền nhạc cực tĩnh tâm, duy trì sự tập trung nhưng vẫn đảm bảo yếu tố thoải mái cho người chơi là hiệu ứng âm thanh khi bạn *cầm* cờ và *đặt* cờ, nói cách dễ hiểu hơn chính là khi bạn ấn chọn quân cờ và chọn vị trí đặt cờ, những âm thanh do tiếng va chạm của gỗ gợi cho chúng ta rất nhiều những liên tưởng đến bộ môn cờ tướng, những âm thanh đó đảm bảo cho người chơi sức nặng của từng nước di chuyển.

# Phân tích sơ bộ về code

Game được viết gồm 3 file là *banco.h*, *banco.cpp* và *main.cpp*. Trong đó, *banco.h* và *banco.cpp* để khởi tạo và định nghĩa các hàm biến phục vụ cho vòng lặp của game trong *main.cpp*.  

Các ô trên bàn cờ được đánh các số -1, 0, 1, phục vụ cho việc vẽ quân cờ và thực hiện logic của game.
****
* `-1`: Ô không có cờ, không được đặt cờ.
* `0`: Ô không có cờ, được đặt cờ.
* `1`: Ô có cờ, được đặt cờ.

### Các hàm chính

* `void drawChess`: vẽ quân cờ.
* `void drawBoard`: vẽ bàn cờ.
* `void resetChess`: đặt lại bàn cờ về trạng thái ban đầu.

* `int LoseOrWin`: kiểm tra trạng thái của bàn cờ sau mỗi nước đi, trả về:
  * `-1`: Hết đường đi tiếp, thua.
  * `0`: Còn đường đi tiếp.
  * `1`: Thắng.

* `bool isInRange`: kiểm tra giá trị có trong khoảng [mn, mx] hay không.
* `bool isAPiece`: kiểm tra xem ô đó có cờ hay không (đánh số 1).
* `bool isEmpty`: kiểm tra xem ô đó có trống và được đặt cờ hay không (đánh số 0).

* `void DisplayText`: hiển thị chữ trên màn hình.
* `std::string timeformat`: chuyển đổi thời gian `ms` sang định dạng `00:00:00.000`.


# Demo

1. [Giới thiệu sơ lược về code và giao diện người chơi.](https://www.youtube.com/watch?v=hzfsCRe1yno)

    Vì một số yếu tố liên quan đến kĩ thuật nên phần cuối của video 1 hơi vị giật lag, em sẽ nó lại về giao diện người chơi và cách giải trong video 2.

2. [Giới thiệu giao diện về game và demo cách giải mẫu.](https://www.youtube.com/watch?v=11u6eTex0Bo)
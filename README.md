# Assignment 02
## 1. Mô tả
Trong assignment này sinh viên được yêu cầu xử lý các dữ liệu thu thập được từ các 
thiết bị như trong assignment 01. Phần này yêu cầu xử lý các công việc tìm kiếm 
trên dữ liệu đặc biệt là khi có rất nhiều dữ liệu. 
Các thiết bị gởi thông tin về vị trí của nó một cách rời rạc và có sai số nhất định. 
Do đó các yếu tố này phải được xem xét khi phần tích dữ liệu nhận được.

Để xác định một điểm có `ở gần` điểm quan sát hay không chúng ta sử dụng ngưỡng 
sai số: `Delta_x`, `Delta_y`. Do nhu cầu tính toán trên một lượng lớn dữ liệu nên
các giải pháp phù hợp cho tìm kiếm nhanh cần phải được cân nhắc. Trong trường hợp 
này, cấu trúc dữ liệu được sử dụng sẽ là cây nhị phân cân bằng AVL. Sinh viên 
được tuỳ ý sử dụng cây để lưu trữ các dữ liệu theo các tiêu chí khác nhau nhằm 
phục vụ tốt nhất cho mục đích tìm kiếm vì yêu cầu về tối ưu thời gian thực thi 
là tiêu chí bắt buộc và sẽ có timeout cho các request.

Một thiết bị có hành trình đi qua vị trí quan sát `R` nếu tồn tại vị trí `P` trong
hành trình của thiết bị thoả điều kiện

    R - Delta_x <= P_x <= R + Delta_x
    R - Delta_y <= P_y <= R + Delta_y

## 2. Dữ liệu
### 2.1. Dữ liệu nhập
Dữ liệu nhập của chương trình được chứa trong file input như sau:

| Header | |
|---|:---------|
| 12 bytes | VRecord data |
|  4 bytes | number of records |
| Content |
|  1| VRecord |
|  2| VRecord |
|  3| VRecord |
|...| ... |

Thông tin chi tiết về record được đặc tả trong cấu trúc VRecord.
Cấu trúc này gồm ID của thiết bị, vị trí (x là longitude, y là latitude),
và timestamp cứa thời gian dữ liệu được gởi đến.
Hàm `distanceVR` được cho sẵn để tính khoảng cách giữa 2 thiết bị, giá 
trị trả về là khoảng cách tính theo km.

Ngoài ra, thiết bị được xem là đang dừng khi toạ độ tại thời điểm hiện tại so với 
thời điểm trước đó cách nhau dưới `5m`.

### 2.2. Dữ liệu xuất
Dữ liệu sinh viên xuất ra cần tuân thủ các quy tắc sau:
 + Số nguyên: không cần định dạng
 + Số thực: độ chính xác *12* chữ số, đã được cài trong `main.cpp`.
 + Các dòng dữ liệu: với mỗi request, sinh viên xuất ra
 thông tin trên cùng một dòng, cách nhau bởi khoảng trắng.
 + Nếu request là dạng command, sinh viên xuất 
 ra `<request>`: `Succeed`/`Failed`.


## 3. Các yêu cầu
Các yêu cầu có thể được xử lý trên database.

| Mã | Mô tả |
| ---------- | ------- |
| CYR`ID` R_y d_y         | Kiểm tra thiết bị `ID` có đi qua vị trí `R` trên trục `y` không |
| CXR`ID` R_x d_x         | Kiểm tra thiết bị `ID` có đi qua vị trí `R` trên trục `x` không |
| NYR`ID` R_y d_y         | Tìm số lượng record của thiết bị `ID` ở gần vị trí `R` trên trục `y` |
| NXR`ID` R_x d_x         | Tìm số lượng record của thiết bị `ID` ở gần vị trí `R` trên trục `x` |
| NPR`ID` R_y R_x d_y d_x | Tìm số lần thiết bị `ID` đi qua vị trí `R`|
| NVR R_y R_x d_y d_x     | Tìm số thiết bị có hành trình đi qua vị trí `R` |
| NRR R_y R_x d_y d_x     | Tìm số record nằm gần vị trí `R` |
| CVP`ID` R_y R_x d_y d_x | Kiểm tra xem thiết bị `ID` có hành trình đi qua vị trí `R` không|
| NRP`ID` R_y R_x d_y d_x | Tìm số lượng record của thiết bị `ID` nằm gần vị trí `R` |

**Lưu ý: nếu có nhiều kết quả có thể trả về thì chọn kết quả đầu tiên theo thứ tự lưu 
trong dữ liệu đầu vào.**


## 5. Hiện thực
**Sinh viên được cung cấp các file sau:**
 - `main.cpp`: mã nguồn chính của chương trình
 - `dsaLib.h`: thư viện các cấu trúc dữ liệu cần dùng
 - `dbLib.h`: file header chứa prototype cần thiết để quản lý database
 - `dbLib.cpp`: mã nguồn hiện thực các chức năng quản lý database
 - `requestLib.h`: file header chứa các prototype cần thiết để quản lý các sự kiện
 - `requestLib.cpp`: mã nguồn hiện thực các hàm xử lý sự kiện

__Sinh viên được cho các hàm sau:__
 - `distanceVR`: tính khoảng cách giữa 2 điểm trên mặt đất với 
 toạ độ (latitude (y), longitude (x)) cho trước.
 - `loadVDB`: đọc file và tải dữ liệu vào danh sách
 - `strPrintTime`: in thời gian ra một chuỗi theo định dạng yêu cầu

Đối với file thư viện `dsaLib.h`, sinh viên được cung cấp sẵn định 
nghĩa cơ bản. Ngoài ra, _để build được chương trình hoàn chỉnh, sinh viên
cần hoàn thiện các hàm còn lại_. Sinh viên có thể thêm các 
tính năng vào thư viện nếu thấy cần thiết.

__processData.cpp__
Sinh viên hiện thực việc xử lý các yêu cầu thông qua hàm __*processRequest*__.
Không được thay đổi prototype của hàm này.

Sinh viên được phép tuỳ biến, chỉnh sửa các file mã nguồn trừ file 
`main.cpp` vì nó sẽ được ghi đè lúc chấm.

**Sinh viên không được sử dụng các thư viện nào khác ngoài các thư viện đã được 
dùng trong framework.**

## Build
Sinh viên thực hiện build bằng lệnh `make` từ command line trên Linux
và chạy file `dsa172a2`. Cú pháp trên linux như sau:
> `./dsa172a2 request.txt sampleData.dat`

trong đó `request.txt` là file chứa danh sách các sự kiện, cách nhau bởi 
khoảng trắng hoặc ký tự xuống dòng.
`sampleData.dat` là file dữ liệu. 

Đối với các bạn dùng VisualStudio trên Windows, các bạn có thể tạo một 
project và thêm các file mã nguồn vào. Nếu không bạn có thể sử dụng hệ 
thống CMake để tự sinh project VS cho mình.
 
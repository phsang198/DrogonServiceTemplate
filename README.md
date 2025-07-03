# DrogonServiceTemplate

# Hướng dẫn cài đặt

## 1. Tải Repo

Chạy `cmd` và thực hiện các bước sau:

### Bước 1: Clone repo

```sh
git clone https://github.com/phsang198/DrogonServiceTemplate.git
```

### Bước 2: Di chuyển vào thư mục repo

```sh
cd /d DrogonServiceTemplate
```

### Bước 3: Thay thế tên service mặc định

Nếu không truyền `OldServiceName`, mặc định là `TemplateService`:

```sh
replaceName.bat YourServiceName
```

Hoặc chỉ định rõ tên cũ:

```sh
replaceName.bat YourServiceName OldServiceName
```

---

## 2. Cài thư viện cho project

### Cách 1: Dùng thư viện đã cấu hình sẵn

Truy cập link sau để tải thư viện:
[Google Drive - DrogonServiceTemplate Libraries](https://drive.google.com/file/d/1NVjwfPkPqbAvN_Dh9m6MVeC1WhEJhhDb/view?usp=sharing)

Sau đó giải nén vào thư mục Lib trong ProjectDir `YourServiceName/Lib`

> ⚠️ **Lưu ý:** Cách này chỉ hỗ trợ các thư viện đã được cấu hình sẵn trong project. Nếu muốn thêm thư viện khác, bạn cần sử dụng `cmake` hoặc `vcpkg`.

### Cách 2: Sử dụng Easy-VS-Configuration

Dùng phần mềm hỗ trợ cấu hình thư viện tại:
[Easy-VS-Configuration](https://github.com/phsang198/Easy-VS-Configuration)

---

## 3. Hướng dẫn chạy project

### Bước 1: Mở file `.sln` bằng Visual Studio

### Bước 2: Thực hiện `Batch Build` cho cả 2 chế độ `Release` và `Debug`

### Bước 3: Cài service bằng file `installService.bat`

Chạy file `installService.bat` trong SolutionDir `DrogonServiceTemplate/X64/Release` với quyền **Administrator**

### Bước 4: Kiểm tra API mẫu

Mở trình duyệt hoặc dùng công cụ như Postman:

```
GET http://0.0.0.0:8765/root/v1/resource
```

---

## 4. Hướng dẫn khác

* Bạn có thể thêm các API khác tương tự như `ClassControl`

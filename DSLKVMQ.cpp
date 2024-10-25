#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;

// cấu trúc Ngay để lưu trữ ngày, tháng, và năm sinh của sinh viên
struct Ngay {
    int ngay, thang, nam;
};

// cấu trúc SinhVien để lưu trữ thông tin sinh viên, bao gồm mã số, họ tên, giới tính (nữ: 0, nam: 1), ngày sinh (dùng Ngay), địa chỉ, lớp, và khoa
struct SinhVien {
    char maSV[9];
    char hoTen[50];
    int gioiTinh;
    Ngay ngaySinh;
    char diaChi[100];
    char lop[12];
    char khoa[7];
};

// cấu trúc Node để tạo một nút trong danh sách liên kết đơn. Mỗi nút chứa một đối tượng SinhVien và một con trỏ link trỏ đến nút tiếp theo trong danh sách
struct Node {
    SinhVien data;
    Node*link;
};

// cấu trúc List để quản lý danh sách liên kết, với con trỏ first trỏ đến nút đầu tiên và last trỏ đến nút cuối cùng của danh sách
struct List {
    Node *first;
    Node *last;
};

// Hàm khởi tạo initList đặt first và last của danh sách thành nullptr, biểu thị danh sách rỗng
void initList(List& ListSV) {
    ListSV.first = nullptr;
    ListSV.last  = nullptr;
};

// Hàm sx tạo một nút mới cho sinh viên sv và thêm nút này vào danh sách theo thứ tự tăng dần của maSV
void sx(List& ListSV, const SinhVien& stu) {
    Node* newAdd = new Node;
    newAdd->data = stu;
    newAdd->link = nullptr;

// Nếu danh sách rỗng hoặc maSV của sinh viên mới nhỏ hơn maSV của sinh viên đầu tiên, nút mới được thêm vào đầu danh sách
    if (!ListSV.first || strcmp(ListSV.first->data.maSV, stu.maSV) > 0) {
        newAdd -> link = ListSV.first;
        ListSV.first = newAdd;
        if (!ListSV.last) {
            ListSV.last = newAdd;
        }
// Nếu không, tìm vị trí thích hợp trong danh sách để giữ thứ tự tăng dần và chèn nút mới vào đó
    } else {
        Node* p = ListSV.first;
        while (p-> link && strcmp(p -> link -> data.maSV, stu.maSV) < 0) {
        p = p -> link;
        }
        newAdd-> link = p-> link;
        p-> link = newAdd;
        if (!newAdd-> link) {
             ListSV.last = newAdd;
        }
    
    }

}

// Hàm  in SV ra
void inSV(const List& ListSV) {
    Node* p = ListSV.first;
    while (p) {
        printf("MSSV: %s, Ten: %s, Gioi Tinh: %d, DOB: %d -%d- %d, Dia Chi: %s, Lop: %s, Khoa: %s\n", p-> data.maSV, p-> data.hoTen, p -> data.gioiTinh, p -> data.ngaySinh.ngay, p -> data.ngaySinh.thang, p -> data.ngaySinh.nam, p-> data.diaChi, p-> data.lop, p-> data.khoa);
        p = p-> link;
    }
}

// Hàm inSVtrungDOB duyệt qua danh sách và in thông tin sinh viên có ngày sinh trùng khớp với ngày tháng năm sinh. Nếu không tìm thấy, thì in là không tìm thấy
void inSVtrungDOB(const List& ListSV, const Ngay& dob) {
    Node* p = ListSV.first;
    bool found = false;
    while (p) {
        if (p->data.ngaySinh.ngay == dob.ngay &&
            p->data.ngaySinh.thang == dob.thang &&
            p->data.ngaySinh.nam == dob.nam) {
            found = true;
            printf("MSSV: %s, Ten: %s\n", p->data.maSV, p->data.hoTen);
        }
        p = p->link;
    }
    if (!found) {
        printf("Không tìm thấy sinh viên cùng ngày sinh\n");
    }
}

int main() {
    List listsv;
    initList(listsv);

    // Add students
    SinhVien stu1 = {"20224455", "Vu Minh Quan", 1, {12, 1, 2004}, "Hanoi", "I02", "IOT"};
    SinhVien stu2 = {"20222239", "Viet-LV", 0, {21, 2, 2001}, "Hanoi", "I02", "IOT"};
    SinhVien stu3 = {"20221234", "Trump", 1, {12, 1, 2004}, "Hanoi", "I02", "IOT"};

    sx(listsv, stu1);
    sx(listsv, stu2);
    sx(listsv, stu3);

    printf("Danh sách sinh viên:\n");
    inSV(listsv);

    Ngay dob = {1, 1, 2000};
    printf("\nSinh viên có cùng ngày sinh 01-01-2000:\n");
    inSVtrungDOB(listsv, dob);


    return 0;
}
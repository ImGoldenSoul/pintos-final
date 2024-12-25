#include "filesys/filesys.h"
#include "filesys/inode.h"
#include "threads/thread.h"
#include "filesys/directory.h"
#include "filesys/file.h"
#include <stdio.h>
#include <string.h>

// Hàm kiểm tra liệt kê quyền truy cập của file
void test_listing_file_access(void) {
    printf("Testing file access listing...\n");

    // Giả sử inode với sector 2 tồn tại
    struct inode *inode = inode_open(2);  // Mở inode với sector 2
    if (inode != NULL) {
        listing_file_access(inode);  // Liệt kê quyền truy cập
        inode_close(inode);  // Đóng inode sau khi sử dụng
    } else {
        printf("Failed to open inode.\n");
    }
}

// Hàm kiểm tra liệt kê quyền truy cập của tất cả file trong hệ thống
void test_listing_all_file_access(void) {
    printf("Testing listing all file access...\n");

    struct dir *dir = dir_open_root();
    if (dir == NULL) {
        printf("Failed to open root directory.\n");
        return;
    }

    struct dir_entry entry;
    while (dir_readdir(dir, &entry)) {
        struct inode *inode = inode_open(entry.inode_sector);
        if (inode != NULL) {
            printf("File: %s\n", entry.name);
            listing_file_access(inode);  // Liệt kê quyền truy cập
            inode_close(inode);  // Đóng inode
        }
    }
    dir_close(dir);  // Đóng thư mục sau khi duyệt hết các file
}

// Hàm main để kiểm tra các chức năng trên
int main(void) {
    printf("Running file access tests...\n");
    test_listing_file_access();  // Kiểm tra quyền truy cập của một file
    test_listing_all_file_access();  // Kiểm tra quyền truy cập của tất cả các file trong hệ thống
    return 0;
}

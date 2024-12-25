// listing_file_access.c

#include <stdio.h>
#include "filesys/inode.h"
#include "filesys/directory.h"
#include "filesys/filesys.h"

// Định nghĩa các quyền truy cập
#define READ  1
#define WRITE 2
#define EXECUTE 4



// Hàm liệt kê quyền truy cập của file
void listing_file_access(struct inode *inode) {
    char access_modes[3][4] = { {'-', '-', '-', '\0'}, {'-', '-', '-', '\0'}, {'-', '-', '-', '\0'} };
    const char* users[] = {"owner", "group", "public"};
    
    // Duyệt qua từng nhóm người dùng để kiểm tra quyền
    for (int i = 0; i < 3; i++) {
        int rights;
        
        // Lấy quyền của nhóm người dùng tương ứng
        if (i == 0) {
            rights = inode->owner;
        } else if (i == 1) {
            rights = inode->group;
        } else {
            rights = inode->public;
        }
        
        // Kiểm tra quyền đọc, ghi, thực thi và lưu vào chuỗi quyền
        if (rights & READ) {
            access_modes[i][0] = 'r';
        }
        if (rights & WRITE) {
            access_modes[i][1] = 'w';
        }
        if (rights & EXECUTE) {
            access_modes[i][2] = 'x';
        }
        
        // In ra quyền của từng nhóm người dùng
        printf("%s: %s\n", users[i], access_modes[i]);
    }
}

// Hàm liệt kê quyền truy cập của tất cả các file và thư mục trong hệ thống
void listing_all_file_access(void) {
    // Lấy danh sách các file và thư mục trong hệ thống (ví dụ thông qua thư mục gốc)
    struct dir *dir = dir_open_root();
    if (dir == NULL) {
        printf("Failed to open root directory.\n");
        return;
    }

    struct dir_entry entry;
    while (dir_readdir(dir, &entry)) {
        struct inode *inode = inode_open(entry.inode_sector);
        if (inode != NULL) {
            printf("File/Folder: %s\n", entry.name);
            listing_file_access(inode);  // Liệt kê quyền truy cập của file/thư mục
            inode_close(inode);
        }
    }
    dir_close(dir);
}

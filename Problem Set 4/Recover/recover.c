//#include <stdio.h>
//#include <stdlib.h>
//#include <stdbool.h>
//#include <string.h>
//
//typedef uint8_t BYTE;
//
//int main(int argc, char *argv[])
//{
//    
//    char *filename = "card.raw";
//    FILE *f = fopen(filename, "r");
//    
//    char names[50][10];
//    BYTE buffer[512];
//    int jpgCount = 0;
//    int number = 1;
//    
//    char jpgname[10];
//    sprintf(jpgname, "%03i.jpg", jpgCount);
//    FILE *img = fopen(jpgname, "w");
//
//    while (number >= 1) {
//        number = (int) fread(buffer, 512, 1, f);
//        img = fopen(jpgname, "w");
//            if (buffer[0] == 0xff && (buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0Xf0) == 0xe0)) {
//                if (jpgCount == 0) {
//                    fwrite(buffer, 512, 1, img);
//                    jpgCount++;
//                } else {
////                    printf("%s\n", jpgname);
//                    strcpy(names[jpgCount], jpgname);
//                    fclose(img);
//                    sprintf(jpgname, "%03i.jpg", jpgCount++);
//                    img = fopen(jpgname, "w");
//                    fwrite(buffer, 512, 1, img);
//                }
//            } else {
//                if (img != NULL) {
//                fwrite(buffer, 512, 1, img);
//                }
//            }
//    }
//    fclose(img);
//    
//    for (int i = 0; i < 50; i++) {
//        printf("%s\n", names[i]);
//    }
//    
////    char *filename = "card.raw";
////    FILE *f = fopen(filename, "r");
////
////    fread(data, size, number, f);
////
////    buffer[0] == 0xff
////    buffer[1] == 0xd8
////    buffer[2] == 0xff
////    (buffer[3] & 0xf0) == 0xe0
////
////    //filenames: ###.jpg, starting at 000.jpg
////    char jpgname[3];
////    sprintf(jpgname, "%03i.jpg", 2);
////
////    FILE *img = fopen(jpgname, "w");
////    fwrite(data, size, number, img);
//}
//
///*
// open memory card
// repeat until end of card:
//    read 512 bytes into a buffer
//    if start of new JPEG
//        if first JPEG
//            ...
//        else
//            ...
//    else
//        if already found JPEG
//            ...
// close any remaining files
// */

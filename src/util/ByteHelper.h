//
// Created by Cory Kacal on 7/26/24.
//

#ifndef UNTITLED_BYTEHELPER_H
#define UNTITLED_BYTEHELPER_H

#endif //UNTITLED_BYTEHELPER_H

class BytesHelper
{
public:
    static unsigned int Gigabyte(unsigned int size) {
        return size * 1000 * 1000 * 1000;
    }

    static unsigned int Megabyte(unsigned int size) {
        return size * 1000 * 1000;
    }

    static unsigned int Kilobyte(unsigned int size) {
        return size * 1000;
    }
};
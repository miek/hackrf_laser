    /*
     * SPI testing utility (using spidev driver)
     *
     * Copyright (c) 2007  MontaVista Software, Inc.
     * Copyright (c) 2007  Anton Vorontsov <avorontsov@ru.mvista.com>
     *
     * This program is free software; you can redistribute it and/or modify
     * it under the terms of the GNU General Public License as published by
     * the Free Software Foundation; either version 2 of the License.
     *
     * Cross-compile with cross-gcc -I/path/to/cross-kernel/include
     */

    #include <stdint.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <fcntl.h>
    #include <sys/ioctl.h>
    #include <linux/spi/spidev.h>

    #define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))

    static void pabort(const char *s)
    {
            perror(s);
            abort();
    }

    static const char *device = "/dev/spidev1.0";
    static uint8_t mode;
    static uint8_t bits = 8;
    static uint32_t speed = 10000000;

    static void transfer(int fd)
    {
            int ret;
            uint8_t tx[] = {
                    0xAB, 0x00, 0x00
            };
            uint8_t rx[ARRAY_SIZE(tx)] = {0, };

            int tfer_count = 4;
            struct spi_ioc_transfer tr[tfer_count];
            int i;
            for (i = 0; i < tfer_count; i++) {
                    tr[i].tx_buf = (unsigned long)tx;
                    tr[i].rx_buf = NULL;
                    tr[i].len = ARRAY_SIZE(tx);
                    tr[i].speed_hz = speed;
                    tr[i].bits_per_word = bits;
                    tr[i].delay_usecs = 0;
                    tr[i].cs_change = 1;
            }
            tr[tfer_count - 1].cs_change = 0;
            for (i = 0; i < 20; i++)
                    ret = ioctl(fd, SPI_IOC_MESSAGE(tfer_count), tr);
            if (ret < 1)
                    pabort("can't send spi message");

            for (ret = 0; ret < ARRAY_SIZE(tx); ret++) {
                    if (!(ret % 6))
                            puts("");
                    printf("%.2X ", rx[ret]);
            }
            puts("");
    }

    int main(void)
    {
            int ret = 0;
            int fd;

            fd = open(device, O_RDWR);
            if (fd < 0)
                    pabort("can't open device");

            /*
             * spi mode
             */
            ret = ioctl(fd, SPI_IOC_WR_MODE, &mode);
            if (ret == -1)
                    pabort("can't set spi mode");

            ret = ioctl(fd, SPI_IOC_RD_MODE, &mode);
            if (ret == -1)
                    pabort("can't get spi mode");

            /*
             * bits per word
             */
            ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
            if (ret == -1)
                    pabort("can't set bits per word");

            ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits);
            if (ret == -1)
                    pabort("can't get bits per word");

            /*
             * max speed hz
             */
            ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
            if (ret == -1)
                    pabort("can't set max speed hz");

            ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
            if (ret == -1)
                    pabort("can't get max speed hz");

            printf("spi mode: %d\n", mode);
            printf("bits per word: %d\n", bits);
            printf("max speed: %d Hz (%d KHz)\n", speed, speed/1000);

            transfer(fd);

            close(fd);

            return ret;
    }



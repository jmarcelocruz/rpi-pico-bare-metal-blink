# Copyright 2024 José Marcelo Marques da Cruz
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

CC = arm-none-eabi-gcc
ARCHFLAGS = -mcpu=cortex-m0plus -mthumb
CFLAGS = -c ${ARCHFLAGS} -Iinclude ${EXTRA_CFLAGS}
LDFLAGS = ${ARCHFLAGS} -Tlinkerscript.ld -nostartfiles -specs nano.specs ${EXTRA_LDFLAGS}

BUILDDIR = build

SOURCES =  syscalls.c startup.c main.c gpio/gpio.c uart/uart.c delay/delay.c
OBJECTS = $(patsubst %.c, ${BUILDDIR}/%.o, ${SOURCES})

firmware.elf: ${BUILDDIR}/firmware.elf

${BUILDDIR}/firmware.elf: ${BUILDDIR}/firmware-no-crc.elf
	rpi-pico-elf-add-crc $< $@

${BUILDDIR}/firmware-no-crc.elf: ${OBJECTS}
	${CC} $^ ${LDFLAGS} -o $@

${OBJECTS}: ${BUILDDIR}/%.o: %.c
	mkdir -p $(dir $@)
	${CC} $^ ${CFLAGS} -o $@

.PHONY: clean
clean:
	rm -r ${BUILDDIR}

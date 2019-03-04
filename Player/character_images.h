const uint8_t run1[] PROGMEM = { 31, 3,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x60, 0x10, 0x08, 0x08, 0x8C, 0x94,
0xE4, 0xA8, 0xB0, 0xA0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x38, 0x44, 0x42, 0xC1, 0xB3, 0x0C, 0xF0, 0x03, 0x0C, 0x10, 0x2E, 0x41, 0x50, 0x56, 0x56,
0xD0, 0x26, 0x10, 0x2F, 0x38, 0x04, 0x84, 0x44, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x0C, 0x12, 0x11, 0x18, 0x10, 0x21, 0x22, 0x24, 0x14, 0xC8, 0xB8, 0x84, 0x82, 0x82, 0xA5, 0xB8,
0xA1, 0xC2, 0x02, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const uint8_t run2[] PROGMEM = { 31, 3,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xE0, 0x18, 0x04, 0x82, 0x42, 0x23, 0xA5,
0xB9, 0x2A, 0xAC, 0x28, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x0C, 0x32, 0x41, 0x80, 0x08, 0x53, 0x24, 0x2B, 0xD0, 0x14, 0x95, 0xD5,
0xB4, 0x99, 0x64, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x48, 0x85, 0x86, 0xA2, 0xA1, 0xB0, 0xCF, 0x04, 0x03, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const uint8_t run3[] PROGMEM = { 31, 3,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x60, 0x10, 0x08, 0x08, 0x8C, 0x94,
0xE4, 0xA8, 0xB0, 0xA0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x70, 0x88, 0x84, 0x84, 0x62, 0xA2, 0x63, 0x14, 0x88, 0x0E, 0x11, 0x20, 0x56, 0x56,
0x50, 0x26, 0x30, 0x2F, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C,
0x12, 0x11, 0x18, 0x10, 0x21, 0x23, 0x21, 0x10, 0x08, 0x08, 0xC9, 0xB2, 0x82, 0x82, 0x82, 0xA6,
0xBA, 0xA2, 0xC2, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const uint8_t idle1[] PROGMEM = { 31, 3,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x18, 0x04, 0x82, 0x42, 0x23, 0xA5,
0xB9, 0x2A, 0xAC, 0x28, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0xE0, 0x18, 0x04, 0x44, 0xC2, 0xE3, 0x04, 0x0B, 0x10, 0x14, 0x15, 0x15,
0x14, 0xE9, 0xC4, 0x47, 0x04, 0x18, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0xC0, 0xA1, 0xA2, 0x92, 0x9A, 0x85, 0x83, 0x82, 0xE4, 0x14, 0x08, 0x14, 0xE4, 0x82,
0x83, 0x85, 0x9A, 0x92, 0xA2, 0xA1, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

const uint8_t idle2[] PROGMEM = { 31, 3,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x18, 0x04, 0x82, 0x42, 0x23, 0x25,
0x39, 0x2A, 0x2C, 0x28, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0xE0, 0x18, 0x04, 0x44, 0xC2, 0xE3, 0x04, 0x0B, 0x10, 0x15, 0x15, 0x15,
0x14, 0xE9, 0xC5, 0x47, 0x04, 0x18, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0xC0, 0xA1, 0xA2, 0x92, 0x9A, 0x85, 0x83, 0x82, 0xE4, 0x14, 0x08, 0x14, 0xE4, 0x82,
0x83, 0x85, 0x9A, 0x92, 0xA2, 0xA1, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const uint8_t falling[] PROGMEM = { 31, 4,
	0x00, 0x00, 0x18, 0x24, 0x42, 0x82, 0x34, 0x18, 0x20, 0xE0, 0x18, 0x04, 0x82, 0x42, 0x23, 0xA5,
0xB9, 0x2A, 0xAC, 0x28, 0xF0, 0x20, 0x18, 0x34, 0x82, 0x42, 0x24, 0x18, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x18, 0xE3, 0x04, 0x0B, 0x10, 0x14, 0x15, 0x15,
0x14, 0x09, 0xE4, 0x9B, 0x84, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x02, 0x02, 0x04, 0x74, 0x88, 0x0C, 0x0A,
0x09, 0x70, 0x40, 0x80, 0x81, 0x8E, 0x90, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x20, 0x20, 0x20, 0x1F, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

const uint8_t fire[] PROGMEM = { 31, 3,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40, 0x40, 0xE0, 0x18, 0x04, 0x82, 0x42, 0x23, 0xA5,
0xB9, 0x2A, 0xAC, 0x28, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x0E, 0x11, 0x20, 0x40, 0x98, 0x84, 0x48, 0x33, 0x04, 0x0B, 0x10, 0x14, 0x15, 0x95,
0x54, 0x29, 0x24, 0x27, 0x22, 0x22, 0x1E, 0x21, 0x21, 0x21, 0x33, 0x1E, 0x12, 0x0C, 0xC0, 0xA0,
0xA0, 0x90, 0x90, 0x88, 0x84, 0x82, 0xC1, 0x22, 0x14, 0x08, 0xC8, 0xB4, 0x84, 0x82, 0x83, 0xA4,
0xB8, 0xA0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

const uint8_t run_fire1[] PROGMEM = { 31, 3,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x60, 0x10, 0x08, 0x08, 0x8C, 0x94,
0xE4, 0xA8, 0xB0, 0xA0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0x80, 0x63, 0x14, 0x88, 0x0E, 0x11, 0x20, 0x56, 0x56,
0x50, 0x26, 0x30, 0x2F, 0xC4, 0x44, 0x3C, 0x42, 0x42, 0x42, 0x66, 0x3C, 0x24, 0x18, 0x00, 0x0C,
0x12, 0x11, 0x18, 0x10, 0x21, 0x23, 0x21, 0x10, 0x08, 0x08, 0xC9, 0xB2, 0x82, 0x82, 0x82, 0xA6,
0xBA, 0xA2, 0xC2, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

const uint8_t run_fire2[] PROGMEM = { 31, 3,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xE0, 0x18, 0x04, 0x82, 0x42, 0x23, 0xA5,
0xB9, 0x2A, 0xAC, 0x28, 0xF0, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x0C, 0x32, 0x41, 0x80, 0x08, 0x53, 0x24, 0x2B, 0xD0, 0x14, 0x95, 0xD5,
0x34, 0x19, 0x14, 0x13, 0x11, 0x11, 0x0F, 0x10, 0x10, 0x10, 0x19, 0x0F, 0x09, 0x06, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x48, 0x85, 0x86, 0xA2, 0xA1, 0xB0, 0xCF, 0x04, 0x03, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

const uint8_t run_fire3[] PROGMEM = { 31, 3,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x60, 0x10, 0x08, 0x08, 0x8C, 0x94,
0xE4, 0xA8, 0xB0, 0xA0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x38, 0x44, 0x42, 0xC1, 0xB3, 0x0C, 0xF0, 0x03, 0x0C, 0x10, 0x2E, 0x41, 0x50, 0x56, 0x56,
0xD0, 0x26, 0x50, 0x4F, 0x44, 0x44, 0x3C, 0x42, 0x42, 0x42, 0x66, 0x3C, 0x24, 0x18, 0x00, 0x00,
0x0C, 0x12, 0x11, 0x18, 0x10, 0x21, 0x22, 0x24, 0x14, 0xC8, 0xB8, 0x84, 0x84, 0x82, 0xA5, 0xB8,
0xA0, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
};

const uint8_t falling_fire[] PROGMEM = { 31, 4,
	0x00, 0x00, 0x18, 0x24, 0x42, 0x82, 0x34, 0x18, 0x20, 0xE0, 0x18, 0x04, 0x82, 0x42, 0x23, 0xA5,
0xB9, 0x2A, 0xAC, 0x28, 0xF0, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x18, 0xE3, 0x04, 0x0B, 0x10, 0x14, 0x15, 0x15,
0x14, 0x09, 0xE4, 0x93, 0x91, 0x11, 0x0F, 0x10, 0x10, 0x10, 0x19, 0x0F, 0x09, 0x06, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x02, 0x02, 0x04, 0x74, 0x88, 0x0C, 0x0A,
0x09, 0x70, 0x40, 0x80, 0x81, 0x8E, 0x90, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x20, 0x20, 0x20, 0x1F, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


const uint8_t female[] PROGMEM = { 128, 18,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xBF, 0xDF, 0x27, 0x3B, 0x0D, 0x02, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x42, 0x10, 0x01, 0x94, 0x40, 0x22, 0x08,
0x40, 0x12, 0x04, 0xE0, 0x08, 0xE2, 0x18, 0x02, 0x08, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0xC0, 0x10, 0xE0, 0x40, 0xA0,
0xC0, 0x70, 0x80, 0x50, 0x80, 0x40, 0x80, 0x80, 0x40, 0x80, 0x02, 0x80, 0x20, 0x00, 0x01, 0x00,
0x00, 0x01, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x08, 0x00,
0x02, 0x28, 0x80, 0x2A, 0x09, 0xB4, 0x43, 0xB5, 0x4B, 0xAF, 0x5F, 0xBF, 0xFF, 0x7F, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x37, 0x0D, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x50, 0x01, 0x10, 0x45, 0x20, 0x91, 0x04, 0x20, 0x01, 0xB0,
0x48, 0xB6, 0x49, 0xB6, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x40, 0x10, 0xC0, 0xA8, 0xA8, 0xF5, 0xA8, 0xF6, 0x59, 0xFE, 0xB8, 0xEF, 0xF8, 0xFF, 0xFD, 0xFE,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFE, 0xFF, 0xFC, 0xFF, 0xFE, 0xF9, 0xF6, 0xF9,
0xF4, 0xE8, 0xD6, 0xF1, 0xCC, 0xD2, 0xE8, 0xD1, 0xE4, 0xD8, 0xA0, 0xE0, 0x44, 0xC0, 0xC0, 0x00,
0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x01, 0x48, 0x82, 0x28, 0x52, 0x80, 0x57, 0xA8, 0xB7, 0x4A, 0xB5, 0x4C, 0xB3, 0xBF, 0xCB, 0x7F,
0xFF, 0x7F, 0x9F, 0x0F, 0x25, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x39, 0x06,
0xE9, 0x16, 0x05, 0xFA, 0x00, 0x08, 0x41, 0x00, 0xD4, 0x20, 0xC0, 0x58, 0x20, 0x80, 0x20, 0xC0,
0xBC, 0x53, 0xEC, 0x5F, 0xF5, 0x5F, 0xFA, 0xEF, 0xFD, 0xDF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xBF, 0xFD, 0xF6, 0xEF, 0xBD, 0xDA, 0x6F, 0xD4,
0x3B, 0xE4, 0x10, 0x80, 0x00, 0x00, 0x00, 0xA0, 0x00, 0xA0, 0x10, 0xC0, 0x20, 0x98, 0x64, 0x99,
0x64, 0x9A, 0x64, 0x1A, 0xEB, 0x34, 0xC9, 0x26, 0xFD, 0x00, 0x2A, 0x41, 0x1A, 0x45, 0x1B, 0x27,
0x8A, 0x21, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x28, 0x97, 0x68, 0x92, 0xEC, 0xB7,
0xEA, 0x95, 0xFF, 0xB5, 0xEF, 0xBB, 0xFE, 0xAB, 0xFE, 0xDB, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF6, 0xFF, 0xAB, 0xFE, 0x57, 0xFA, 0x55,
0xFF, 0xA2, 0x5D, 0x22, 0x90, 0x44, 0x2A, 0x09, 0xF6, 0x04, 0x09, 0x24, 0x02, 0x09, 0x04, 0x13,
0x14, 0x0B, 0x00, 0x03, 0x04, 0x01, 0x02, 0x00, 0x02, 0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
0x0A, 0x30, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x28, 0x07, 0x58, 0xA7, 0x5D, 0xB6,
0x3B, 0x9E, 0x2B, 0x9E, 0x9B, 0x9E, 0x0F, 0x9E, 0x2F, 0x1F, 0x1F, 0x3F, 0x1F, 0x3F, 0x1F, 0x3F,
0x3F, 0x3F, 0x3F, 0x7F, 0x3F, 0xFF, 0x7F, 0xBF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x7F, 0x7F, 0x3F, 0x35, 0x3F, 0x17,
0x3A, 0x15, 0x2A, 0x11, 0xAC, 0xD3, 0x2C, 0xD1, 0x00, 0x09, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x00, 0xD0, 0xED, 0xA2, 0x5D, 0xD2,
0x2D, 0x42, 0x07, 0x01, 0x02, 0x41, 0x01, 0x41, 0x01, 0x01, 0x40, 0x01, 0xC0, 0xE0, 0xC0, 0xC0,
0x90, 0x00, 0x60, 0x80, 0x54, 0x00, 0x6D, 0x82, 0x6C, 0xBB, 0xEF, 0xFB, 0xFF, 0xFF, 0xFF, 0xFD,
0xFF, 0x4F, 0x37, 0x0B, 0x05, 0x03, 0x80, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x02,
0x00, 0x06, 0x01, 0x04, 0x02, 0x08, 0x21, 0x8E, 0x41, 0x14, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10,
0x00, 0x10, 0x00, 0x50, 0x04, 0x00, 0x20, 0x80, 0x00, 0xA0, 0x00, 0x80, 0x40, 0xB2, 0x40, 0x98,
0x20, 0x50, 0x06, 0x00, 0x00, 0x00, 0x00, 0x40, 0xB0, 0x6D, 0xBA, 0xEF, 0xBF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFC, 0xFD, 0xFC, 0xFA, 0xFC, 0xF8, 0xFD, 0xF8, 0xFE, 0xF8, 0xFD, 0xFC, 0xFE,
0xFE, 0xFE, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xF5, 0xAD, 0xFC, 0xFE, 0xFD, 0xFB, 0xFC, 0xE8, 0xF5, 0xD0, 0xF1, 0xD0, 0xB3, 0xD9, 0xC0,
0xF8, 0xC0, 0xB8, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0xE8, 0xCA, 0x20,
0x00, 0x00, 0x40, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x28, 0x82,
0x40, 0x45, 0x20, 0x92, 0x08, 0x65, 0x0A, 0xA1, 0x04, 0x52, 0x04, 0x11, 0x84, 0x41, 0x54, 0x2A,
0x04, 0x89, 0x20, 0x02, 0x80, 0x30, 0x8A, 0x71, 0x8E, 0x71, 0x9F, 0x6A, 0xD5, 0xBF, 0x6A, 0x9F,
0xF5, 0xBF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xBF, 0xFF, 0x5F, 0xEF, 0xBF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFE, 0xED, 0x56, 0xBB, 0xEF, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xBF,
0xFD, 0x57, 0xFF, 0x52, 0xBD, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x2C, 0x53, 0xA4, 0x93, 0xC5,
0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x03, 0x00,
0x82, 0x40, 0x01, 0x60, 0x02, 0x28, 0x04, 0x01, 0x00, 0x04, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x10, 0xAA, 0x25, 0x98, 0x67, 0x98, 0x67, 0x98, 0x67, 0x98, 0x67, 0x9A, 0x65,
0x9B, 0xEE, 0x17, 0xFA, 0x57, 0xBD, 0x77, 0x9F, 0x6F, 0x3F, 0x97, 0x2D, 0xD7, 0x6F, 0xF3, 0x7D,
0xFE, 0xFF, 0xFF, 0xFF, 0xF2, 0xEF, 0xEF, 0xE7, 0xEF, 0xE1, 0xC6, 0x43, 0x07, 0x1F, 0x0B, 0x1F,
0x0F, 0x87, 0x07, 0xE1, 0x86, 0xE9, 0x3F, 0xD5, 0x7F, 0xAB, 0x57, 0x2F, 0x5F, 0x3B, 0xEF, 0x17,
0xFA, 0x15, 0xF7, 0x1D, 0x06, 0x40, 0x00, 0x00, 0xC0, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x0B, 0x04, 0x07, 0x09,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x20, 0xC0, 0x00, 0x00, 0x80, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x05, 0x0A, 0x52, 0xAD, 0x52, 0xAD, 0x56, 0xAB, 0xBC, 0xD3, 0xAC,
0x53, 0xAC, 0x7B, 0x8D, 0x72, 0xDD, 0xF8, 0xFE, 0xF1, 0xE6, 0xE3, 0xE3, 0xC3, 0x87, 0xC7, 0x8F,
0x4F, 0x97, 0xCF, 0x1F, 0xCF, 0xDF, 0xD7, 0xDF, 0xF7, 0xDF, 0xD7, 0xFF, 0xDF, 0xEF, 0xEF, 0xD6,
0xCF, 0xD6, 0x4F, 0x85, 0x07, 0x86, 0xC1, 0x87, 0xF2, 0xF1, 0xFE, 0xF8, 0xFE, 0xF8, 0x7D, 0x12,
0xDD, 0x22, 0x09, 0x00, 0x04, 0x08, 0x0E, 0x19, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x02, 0xD4, 0x00, 0x00, 0x20, 0x80, 0x00, 0x40, 0xA0, 0xC0, 0x00, 0x80, 0x00, 0x00,
0x00, 0x00, 0x00, 0x80, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x04, 0x0B, 0x10, 0x02, 0x20,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x05, 0x15, 0x0A, 0x57, 0x2C,
0xDF, 0x62, 0xBD, 0xD7, 0xAF, 0x7A, 0xDF, 0xBF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFB, 0xFE,
0xE9, 0xFE, 0xE9, 0xF7, 0xF5, 0xF7, 0xFB, 0xE7, 0xFF, 0xEB, 0xCF, 0xF5, 0x8F, 0xF5, 0x4E, 0xEB,
0xA4, 0xD7, 0x68, 0xB5, 0x4A, 0xF5, 0x5E, 0xF7, 0x5B, 0xBD, 0x5F, 0x27, 0x1B, 0x05, 0x0A, 0x03,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x40, 0x00, 0xA2, 0x20, 0x10, 0x40, 0x04, 0x21, 0x65, 0xA4, 0x93, 0x50, 0x61, 0xF8, 0x12, 0xEC,
0x00, 0x03, 0x01, 0x09, 0x00, 0x01, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x80, 0x00, 0x80,
0x00, 0x01, 0x04, 0x03, 0x0E, 0x11, 0x2F, 0x2A, 0x35, 0x4F, 0xBB, 0x6F, 0xBF, 0x7F, 0xDF, 0xFF,
0xFF, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0x7E, 0xF7, 0x5B, 0x7F, 0x15, 0x0F, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x80, 0x24, 0xC2, 0x08, 0xC6, 0x01, 0x26, 0x49, 0x04, 0x2B, 0x12, 0xAD, 0xD7, 0xAB, 0x64, 0xF3,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0xA0, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x95, 0x6A, 0xBF,
0xF4, 0xAA, 0xF4, 0xA8, 0xD0, 0x40, 0xA0, 0x00, 0x80, 0x00, 0x00, 0x01, 0x00, 0x03, 0x01, 0x02,
0x07, 0x05, 0x0F, 0x0B, 0x0F, 0x17, 0x0F, 0x1B, 0x0F, 0x17, 0x1F, 0x0F, 0x1F, 0x0B, 0x0F, 0x07,
0x05, 0x07, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08,
0x00, 0x36, 0x29, 0x2E, 0xD2, 0x6D, 0xB6, 0xEE, 0xBC, 0xE8, 0xBD, 0xFA, 0xFB, 0xFA, 0xFB, 0xFB,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x52, 0xA1, 0x08, 0x20, 0x90, 0x62, 0x90, 0xAA, 0x75, 0xDB,
0xBF, 0xFF, 0xFD, 0xAF, 0xFA, 0xDF, 0x75, 0xFF, 0x58, 0xEB, 0xD4, 0x68, 0x92, 0xE8, 0x00, 0xD0,
0x00, 0x40, 0x00, 0x40, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x05, 0x0A, 0x0D, 0xF6, 0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x40, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x06, 0xAA, 0x0F, 0x7A,
0x8D, 0x77, 0x9F, 0xFA, 0xAF, 0x7D, 0xAB, 0x7F, 0xDB, 0xAE, 0xFB, 0x55, 0xBE, 0xF3, 0x2C, 0xD7,
0x68, 0x97, 0x68, 0x95, 0x4A, 0xA0, 0x04, 0x20, 0x48, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10,
0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x55, 0xFA, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0x68, 0xD0, 0x68, 0x80, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x04, 0x00, 0x00,
0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x80, 0x40, 0x80, 0x08, 0x01, 0x02, 0x00, 0x00, 0x01,
0x84, 0x01, 0x02, 0x3F, 0xEA, 0x95, 0x77, 0xDC, 0xF7, 0x2D, 0xDA, 0x6F, 0x99, 0x66, 0x9D, 0x63,
0x9C, 0x23, 0xCC, 0x31, 0xCA, 0xB4, 0x49, 0xB6, 0x49, 0x12, 0x40, 0xAC, 0x10, 0x80, 0x00, 0x00,
0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xA7, 0x40, 0x07, 0x00, 0xFC, 0x01, 0x00, 0x00, 0x28, 0x04, 0x40, 0x00, 0x24, 0x80, 0x00, 0x40,
0xA0, 0x10, 0x88, 0xE0, 0xE0, 0xE0, 0xE0, 0xEC, 0x70, 0xE0, 0x70, 0xF0, 0xF0, 0xF0, 0xE0, 0xE0,
0xC0, 0x8A, 0x84, 0x91, 0x0C, 0x12, 0x2C, 0x1B, 0x1D, 0x1E, 0x09, 0x00, 0x40, 0x70, 0x00, 0x18,
0x82, 0xA0, 0x48, 0xF0, 0x5F, 0xF6, 0xDB, 0xAE, 0x79, 0xCE, 0x31, 0xCF, 0x30, 0xCF, 0x30, 0xCF,
0xB0, 0x6F, 0x90, 0xFF, 0xAA, 0x56, 0xA9, 0x52, 0x55, 0x00, 0x2B, 0xD0, 0xAC, 0xD2, 0x6D, 0xFA,
0xFE, 0xFF, 0xFC, 0xF8, 0xF8, 0xE0, 0xE0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
0xF4, 0x00, 0xD8, 0x00, 0xF8, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xAE, 0x7B, 0xCD, 0x74, 0xA1, 0x56, 0x88, 0x20, 0x00, 0x00, 0x04, 0xA0, 0x0A, 0x08, 0x04, 0x0B,
0x45, 0x9E, 0x3F, 0xDF, 0xBF, 0x7F, 0xBF, 0x3F, 0xBF, 0x3E, 0x5D, 0x38, 0x03, 0x81, 0xDF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFE, 0xFD, 0xFC, 0xFE, 0xF8, 0xF7, 0xFC,
0xF7, 0xFD, 0xCB, 0xFF, 0xD5, 0xBF, 0x76, 0xDB, 0x6D, 0xB7, 0xDC, 0x2B, 0xD4, 0x37, 0xC8, 0x7F,
0xAA, 0xFD, 0x5B, 0xFE, 0xAF, 0xF9, 0xD6, 0xFD, 0xF7, 0xF8, 0xE2, 0xE3, 0xDE, 0xBF, 0x3F, 0x3F,
0x7F, 0x7F, 0x3F, 0x3F, 0x3F, 0x0F, 0x03, 0x12, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
0x03, 0x0A, 0x52, 0xAD, 0xDA, 0x25, 0xDB, 0x75, 0xCF, 0x37, 0xDF, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF
};


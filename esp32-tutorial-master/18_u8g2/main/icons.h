const uint8_t hourglass_empty[] = {
  0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0x00, 0x80, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0x1F, 0x00, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x00, 
  0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x80, 0x03, 0x00, 
  0x00, 0x18, 0x00, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x38, 0x00, 0x00, 
  0x00, 0xC0, 0x01, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0xC0, 0x01, 0x00, 
  0x00, 0x38, 0x00, 0x00, 0x00, 0xC0, 0x01, 0x00, 0x00, 0x30, 0x00, 0x00, 
  0x00, 0xC0, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 
  0x00, 0x70, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 
  0x00, 0x60, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 
  0x00, 0xC0, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 
  0x00, 0x38, 0x00, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x18, 0x00, 0x00, 
  0x00, 0x80, 0x03, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 
  0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x06, 0x00, 0x00, 
  0x00, 0x00, 0x0C, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x18, 0x02, 
  0x80, 0x01, 0x00, 0x00, 0x00, 0x00, 0x38, 0xFE, 0xE7, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x60, 0xFE, 0x67, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xF9, 
  0x39, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xE7, 0x1E, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x4E, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9C, 
  0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x98, 0x01, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9C, 
  0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x07, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x80, 0x07, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x01, 
  0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x70, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x30, 0x00, 0xC0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 
  0x80, 0x01, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x10, 0x03, 0x00, 0x00, 
  0x00, 0x00, 0xE6, 0xFD, 0x7F, 0x06, 0x00, 0x00, 0x00, 0x00, 0xF3, 0xFF, 
  0xFF, 0x0E, 0x00, 0x00, 0x00, 0x00, 0xF3, 0xFF, 0xFF, 0x0C, 0x00, 0x00, 
  0x00, 0x80, 0xF9, 0xFF, 0xFF, 0x19, 0x00, 0x00, 0x00, 0xC0, 0xF9, 0xFF, 
  0xFF, 0x39, 0x00, 0x00, 0x00, 0xC0, 0xFC, 0xFF, 0xFF, 0x33, 0x00, 0x00, 
  0x00, 0x60, 0xFE, 0xFF, 0xFF, 0x67, 0x00, 0x00, 0x00, 0x60, 0xFE, 0xFF, 
  0xFF, 0x67, 0x00, 0x00, 0x00, 0x70, 0xFE, 0xFF, 0xFF, 0xE7, 0x00, 0x00, 
  0x00, 0x30, 0xFF, 0xFF, 0xFF, 0xCF, 0x00, 0x00, 0x00, 0x30, 0xFF, 0xFF, 
  0xFF, 0xCF, 0x00, 0x00, 0x00, 0x38, 0xFF, 0xFF, 0xFF, 0xCF, 0x01, 0x00, 
  0x00, 0xB8, 0xFF, 0xFF, 0xFF, 0xDF, 0x01, 0x00, 0x00, 0xB8, 0xFF, 0xFF, 
  0xFF, 0xDF, 0x01, 0x00, 0x00, 0x98, 0xFF, 0xFF, 0xFF, 0x9F, 0x01, 0x00, 
  0x00, 0x9C, 0xFF, 0xFF, 0xFF, 0x9F, 0x03, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0x0F, 0x00, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x00, 
  0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x00, 0x80, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0x1F, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0x00, 
  };
  
const uint8_t hourglass_half[] = {
  0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0x00, 0x80, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0x1F, 0x00, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x00, 
  0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x80, 0x03, 0x00, 
  0x00, 0x18, 0x00, 0x00, 0x00, 0x80, 0x01, 0x00, 0x00, 0x38, 0x00, 0x00, 
  0x00, 0xC0, 0x01, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0xC0, 0x01, 0x00, 
  0x00, 0x38, 0x00, 0x00, 0x00, 0xC0, 0x01, 0x00, 0x00, 0x30, 0x00, 0x00, 
  0x00, 0xC0, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 
  0x00, 0x70, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 
  0x00, 0x60, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 
  0x00, 0xC0, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 
  0x00, 0x38, 0x00, 0x00, 0x00, 0x80, 0x01, 0x00, 0x08, 0x18, 0x00, 0x00, 
  0x00, 0x80, 0x43, 0xFD, 0xFF, 0x0C, 0x00, 0x00, 0x00, 0x00, 0xE7, 0xFF, 
  0x7F, 0x0C, 0x00, 0x00, 0x00, 0x00, 0xC6, 0xFF, 0x7F, 0x06, 0x00, 0x00, 
  0x00, 0x00, 0x8C, 0xFF, 0x3F, 0x03, 0x00, 0x00, 0x00, 0x00, 0x98, 0xFF, 
  0x9F, 0x01, 0x00, 0x00, 0x00, 0x00, 0x38, 0xFE, 0xCF, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x60, 0xFE, 0x73, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xF9, 
  0x39, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xE7, 0x1E, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x4E, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9C, 
  0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x98, 0x01, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9C, 
  0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0E, 0x07, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x80, 0x07, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x01, 
  0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x70, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x30, 0x00, 0xC0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 
  0x80, 0x01, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x03, 0x00, 0x00, 
  0x00, 0x00, 0x0E, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 
  0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x0C, 0x00, 0x00, 
  0x00, 0x80, 0x01, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 
  0x00, 0x30, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 
  0x00, 0x60, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x60, 0xF0, 0x27, 
  0x00, 0x60, 0x00, 0x00, 0x00, 0x70, 0xFE, 0xFF, 0x6F, 0xE0, 0x00, 0x00, 
  0x00, 0x30, 0xFF, 0xFF, 0xFF, 0xCF, 0x00, 0x00, 0x00, 0x30, 0xFF, 0xFF, 
  0xFF, 0xCF, 0x00, 0x00, 0x00, 0x38, 0xFF, 0xFF, 0xFF, 0xCF, 0x01, 0x00, 
  0x00, 0xB8, 0xFF, 0xFF, 0xFF, 0xDF, 0x01, 0x00, 0x00, 0xB8, 0xFF, 0xFF, 
  0xFF, 0xDF, 0x01, 0x00, 0x00, 0x98, 0xFF, 0xFF, 0xFF, 0x9F, 0x01, 0x00, 
  0x00, 0x9C, 0xFF, 0xFF, 0xFF, 0x9F, 0x03, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0x0F, 0x00, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x00, 
  0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x00, 0x80, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0x1F, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0x00, 
  };

const uint8_t hourglass_full[] = {
  0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x00, 0x80, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0x1F, 0x00, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x00, 
  0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0x0F, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x80, 0x01, 0x00, 
  0x00, 0x18, 0x00, 0x00, 0x00, 0xC0, 0x01, 0x00, 0x00, 0x3C, 0x00, 0x00, 
  0x00, 0xC0, 0x01, 0x00, 0x00, 0x38, 0x04, 0x00, 0x00, 0xC0, 0x01, 0x00, 
  0x00, 0x38, 0xFF, 0x00, 0x00, 0xC0, 0x01, 0x00, 0x00, 0x30, 0xFF, 0x1F, 
  0x00, 0xC0, 0x00, 0x00, 0x00, 0x30, 0xFF, 0xFF, 0x07, 0xC0, 0x00, 0x00, 
  0x00, 0x70, 0xFE, 0xFF, 0xFF, 0xE7, 0x00, 0x00, 0x00, 0x60, 0xFE, 0xFF, 
  0xFF, 0x67, 0x00, 0x00, 0x00, 0x60, 0xFC, 0xFF, 0xFF, 0x73, 0x00, 0x00, 
  0x00, 0xC0, 0xFC, 0xFF, 0xFF, 0x33, 0x00, 0x00, 0x00, 0xC0, 0xF9, 0xFF, 
  0xFF, 0x39, 0x00, 0x00, 0x00, 0x80, 0xF9, 0xFF, 0xFF, 0x19, 0x00, 0x00, 
  0x00, 0x80, 0xF3, 0xFF, 0xFF, 0x0C, 0x00, 0x00, 0x00, 0x00, 0xE7, 0xFF, 
  0x7F, 0x0E, 0x00, 0x00, 0x00, 0x00, 0xE6, 0xFF, 0x7F, 0x07, 0x00, 0x00, 
  0x00, 0x00, 0xCC, 0xFF, 0x1F, 0x03, 0x00, 0x00, 0x00, 0x00, 0x98, 0xFF, 
  0xDF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x78, 0xFF, 0xE7, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0xE0, 0xFE, 0x73, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0xF9, 
  0x3D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x77, 0x0E, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xCE, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9C, 
  0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90, 0x01, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xD8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x9C, 
  0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x07, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x80, 0x03, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x01, 
  0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x60, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x38, 0x00, 0xC0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x1C, 0x00, 
  0x80, 0x01, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x03, 0x00, 0x00, 
  0x00, 0x00, 0x06, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 
  0x00, 0x0E, 0x00, 0x00, 0x00, 0x80, 0x03, 0x00, 0x00, 0x0C, 0x00, 0x00, 
  0x00, 0x80, 0x01, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 
  0x00, 0x38, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 
  0x00, 0x60, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 
  0x00, 0x60, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 
  0x00, 0x30, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x38, 0x78, 0x01, 
  0x00, 0xC0, 0x01, 0x00, 0x00, 0x38, 0xFF, 0xFF, 0x9B, 0xC6, 0x01, 0x00, 
  0x00, 0xB8, 0xFF, 0xFF, 0xFF, 0xDF, 0x01, 0x00, 0x00, 0xBC, 0xFF, 0xFF, 
  0xFF, 0xDF, 0x03, 0x00, 0x00, 0x98, 0xFF, 0xFF, 0xFF, 0x9F, 0x01, 0x00, 
  0x00, 0x9C, 0xFF, 0xFF, 0xFF, 0xDF, 0x03, 0x00, 0x80, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0x0F, 0x00, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x00, 
  0xC0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x00, 0x80, 0xFF, 0xFF, 0xFF, 
  0xFF, 0xFF, 0x1F, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x0F, 0x00, 
  };

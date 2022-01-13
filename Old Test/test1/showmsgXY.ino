void showmsgXY(int x, int y, int sz, const GFXfont *f, const char *msg)
{
int16_t x1, y1;
uint16_t wid, ht;
tft.setFont(f);
tft.setCursor(x, y);
tft.setTextColor(0x0000);
tft.setTextSize(sz);
tft.print(msg);
}

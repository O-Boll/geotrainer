#include "Typesetter.h"

#include "../img/Img.h"

Typesetter::Typesetter() {
  screen = nullptr;
  width = height = 0;
  setBox(0, 0, 0, 0);
  setClipping(0, 0, 0, 0);
  text_w = text_h = 0;
  def_life_span = -1.0;
  def_color = 0;
  bool add_top = false;
  max_number_of_lines = 10;
  max_line_size = 1000;
  slow_typing = false;
  typing_counter = 0;
  typing_counter_offset = 0;
  typing_speed = 100;
}

Typesetter::Typesetter(Uint32* n_screen, int n_width, int n_height, Typewriter *n_tw) {
  screen = n_screen;
  width  = n_width;
  height = n_height;
  tw = n_tw;
  def_life_span = -1.0;
  def_color = 0xFFCCCCCC;
  setBox(0, 0, n_width, n_height);
  setClipping(0, 0, n_width, n_height);
  text_w = text_h = 0;
  add_top = false;
  max_number_of_lines = 10;
  max_line_size = 1000;
  slow_typing = false;
  typing_counter = 0;
  typing_counter_offset = 0;
  typing_speed = 100;
}

void Typesetter::setBox(int n_x, int n_y, int n_w, int n_h) {
  box.x = n_x;
  box.y = n_y;
  box.w = n_w;
  box.h = n_h;
}

void Typesetter::setClipping(int n_x, int n_y, int n_w, int n_h ) {
  clipping_box.x = n_x;
  clipping_box.y = n_y;
  clipping_box.w = n_w;
  clipping_box.h = n_h;
}

void Typesetter::addLine(std::string s, double life, Uint32 color) {
  if(lines.size() >= max_number_of_lines)
    return;
  Line l;
  l.s = s;
  l.color = color;
  l.in_queue = true;
  l.life = Timer(life);
  l.n_chars = 0;
  for(int i = 0; i < s.size(); i++) {
    Img* img = tw->getCharacter(s[i]);
    if(img != nullptr)
      l.n_chars++;
  }
  l.n_typed_chars = 0; /* only relevent when slow_typing == true */
  bool typing_done = true;
  int char_counter = 0;
  for(auto& l : lines) {
    if(l.n_typed_chars < l.n_chars) {
      typing_done = false;
      break;
    }
    char_counter += l.n_chars;
  }
  if(typing_done)
    typing_counter_offset = typing_counter - char_counter;
  if(add_top) { lines.insert(lines.begin(), l); }
  else        { lines.push_back(l); }
  calcTextSize();
}

void Typesetter::addLine(std::string s, double life) {
  addLine(s, life, def_color);
}

void Typesetter::addLine(std::string s) {
  addLine(s, def_life_span, def_color);
}

void Typesetter::setLineColor(int n, Uint32 color) {
  if(n >= 0 && n < lines.size())
    lines[n].color = color;
}

void Typesetter::setDefLineColor(int n) {
  setLineColor(n, def_color);
}

void Typesetter::setColor(Uint32 color) {
  for(int n = 0; n < (int) lines.size(); n++)
    setLineColor(n, color);
}

void Typesetter::clearLines() {
  lines.clear();
  calcTextSize();
}

void Typesetter::removeLine(int n) {
  if(n >= 0 && n < lines.size()) {
    typing_counter_offset += lines[n].n_typed_chars;
    lines.erase(lines.begin() + n);
    calcTextSize();
  }
}

int Typesetter::getNumberOfLines() const {
  return lines.size();
}

int Typesetter::getX() const {
  return box.x;
}

int Typesetter::getY() const {
  return box.y;
}

int Typesetter::getW() const {
  return box.w;
}

int Typesetter::getH() const {
  return box.h;
}

int Typesetter::getTextWidth() const {
  return text_w;
}

int Typesetter::getTextHeight() const {
  return text_h;
}

void Typesetter::setSlowTyping(bool n_slow_typing) {
  slow_typing = n_slow_typing;
  if(slow_typing) {
    typing_timer = Timer();
    typing_counter = 0;
    typing_counter_offset = 0;
  }
}

void Typesetter::step() {
  calcTextSize();
  typing_counter = typing_timer.getElapsedMilliseconds() * typing_speed / 1000;
  int char_counter = 0;
  for(auto& l : lines) {
    if(char_counter + l.n_chars > typing_counter - typing_counter_offset) {
      l.n_typed_chars = char_counter + l.n_chars - (typing_counter - typing_counter_offset);
      break;
    }
    l.n_typed_chars = l.n_chars;
    char_counter += l.n_chars;
  }
  for(int n = 0; n < lines.size(); n++) {
    Line line = lines[n];
    if(line.life.isExpired()) {
      removeLine(n);
      n--;
    }
  }
}

void Typesetter::calcTextSize() {
  text_w = text_h = 0;
  int cur_y = box.y;
  for(int n = 0; n < lines.size() && cur_y < box.y + box.h; n++) {
    Line line = lines[n];
    const char *str = line.s.c_str();
    int cur_x = box.x;
    while(*str != '\0' && cur_y < box.y + box.h) {
      Img* i = tw->getCharacter(*str);
      if(i == nullptr) {
        str++;
        continue;
      }
      if(*str == ' ') {
        int temp_x = cur_x;
        const char *temp_str = str;
        temp_str++;
        temp_x += i->getWidth();
        while(*temp_str != ' ' && *temp_str != '\0') {
          Img *temp_i = tw->getCharacter(*temp_str);
          if(temp_i == nullptr) {
            temp_str++;
            continue;
          }
          temp_x += temp_i->getWidth();
          if(temp_x >= box.x + box.w) {
            str++;
            i = tw->getCharacter(*str);
            cur_y += tw->getLeading();
            cur_x = box.x;
            break;
          }
          temp_str++;
        }
      }
      else if(cur_x + i->getWidth() >= box.x + box.w) {
        cur_y += tw->getLeading();
        cur_x = box.x;
      }
      cur_x += i->getWidth();
      if(cur_x - box.x > text_w)
        text_w = cur_x - box.x + 1; /* + 1 since difference 0 means 1 pixel wide */
      str++;
    }
    cur_y += tw->getLeading();
  }
  text_h = cur_y + 1 > box.y + box.h ? box.h : cur_y - box.y + 1;
}

void Typesetter::type() const {
  int cur_y = box.y, char_count = 0;
  for(int n = 0; n < lines.size() && cur_y < box.y + box.h; n++) {
    if(slow_typing && char_count > typing_counter - typing_counter_offset)
      return;
    Line line = lines[n];
    const char *str = line.s.c_str();
    typeString(cur_y, str, line.color, char_count);
    cur_y += tw->getLeading();
  }
}

void Typesetter::typeString(int& y, const char *str, Uint32 color, int& char_count) const {
  int x = box.x;
  while(*str != '\0' && y < box.y + box.h
                     && y < clipping_box.y + clipping_box.h) {
    Img* i = tw->getCharacter(*str);
    if(i == nullptr) {
      str++;
      continue;
    }
    if(*str == ' ') { /* check the length (in pixels) of the next word */
      int temp_x = x;
      const char *temp_str = str;
      temp_str++;
      temp_x += i->getWidth();
      while(*temp_str != ' ' && *temp_str != '\0') {
        Img *temp_i = tw->getCharacter(*temp_str);
        if(temp_i == nullptr) {
          temp_str++;
          continue;
        }
        temp_x += temp_i->getWidth();
        if(temp_x >= box.x + box.w) {
          str++;
          i = tw->getCharacter(*str);
          y += tw->getLeading();
          x = box.x;
          break;
        }
        temp_str++;
      }
    }
    else if(x + i->getWidth() >= box.x + box.w) {
      y += tw->getLeading();
      x = box.x;
    }
    if(slow_typing && char_count > typing_counter - typing_counter_offset)
      return;
    typeCharacter(i, x, y, color);
    char_count++;
    x += i->getWidth();
    str++;
  }
}


void Typesetter::typeCharacter(Img *c, int x, int y, Uint32 color) const {
  int min_x, max_x, min_y, max_y, start_u, u, v;
  min_x = box.x < 0 ? 0 : box.x;
  min_x = min_x < clipping_box.x ? clipping_box.x : min_x;
  min_x = x < min_x ? min_x : x;
  max_x = box.x + box.w < width ? box.x + box.w : width;
  max_x = clipping_box.x + clipping_box.w < max_x
          ? clipping_box.x + clipping_box.w : max_x;
  max_x = x + c->getWidth() < max_x ? x + c->getWidth() : max_x;
  min_y = box.y < 0 ? 0 : box.y;
  min_y = min_y < clipping_box.y ? clipping_box.y : min_y;
  min_y = y < min_y ? min_y : y;
  max_y = box.y + box.h < height ? box.y + box.h : height;
  max_y = clipping_box.y + clipping_box.h < max_y
          ? clipping_box.y + clipping_box.h : max_y;
  max_y = y + c->getHeight() < max_y ? y + c->getHeight() : max_y;
  start_u = min_x - x;
  v = min_y - y;
  for(int c_y = min_y; c_y < max_y; c_y++) {
    u = start_u;
    for(int c_x = min_x; c_x < max_x; c_x++) {
      if(c->getPixelAt(u, v) != 0xFF00FF00) {
        screen[c_y * width + c_x] = color;
        if(c_y + 1 < max_y && c_x + 1 < max_x)
          screen[(c_y + 1) * width + (c_x + 1)] = 0xFF000000;
      }
      u++;
    }
    v++;
  }
}

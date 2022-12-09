#include "health.h"

Health::Health() {
    setPixmap(_img);
}

void Health::decreaseHealth() {
    _health--;
    setPixmap(_img.copy(0, 0, _health * 69, _img.height()));
}

#include "button.h"

void button::ButtonClicked(){
    emit iChanged(this);
}

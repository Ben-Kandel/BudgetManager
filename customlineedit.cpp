#include "customlineedit.h"

void customlineedit::EditingFinished(){
    emit iChanged(this);
}

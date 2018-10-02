#ifndef Utils_h
#define Utils_h


template<typename T>
void debug(const T& message, bool back = true)
{
  if (IS_DEBUG_MODE) {
    if (back) {
      Serial.println(message);
    } else {
      Serial.print(message);
    }
  }
}

#endif

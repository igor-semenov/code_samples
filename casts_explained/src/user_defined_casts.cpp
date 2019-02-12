
class Simple {
 public:
  operator int() const { return 1; }
  explicit operator bool() const { return true; }
};

int main(int, char**) {

  Simple s;

  return 0;

}


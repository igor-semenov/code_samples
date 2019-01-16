
class Simple {
public:
  Simple() : a_(0), b_(0) {}
  Simple(int a) : a_(a), b_(0) {}
  Simple(int a, int b) : a_(a), b_(b) {}
  operator bool() const { return true; }
private:
  int a_, b_;
};

class SimpleExplicit {
public:
  explicit SimpleExplicit() : a_(0), b_(0) {}
  explicit SimpleExplicit(int a) : a_(a), b_(0) {}
  explicit SimpleExplicit(int a, int b) : a_(a), b_(b) {}
  explicit operator bool() const { return true; }
private:
  int a_, b_;
};

template <typename S>
void someFunc(const S& s) {
}

int main(int, char**) {

  Simple s1(11);
  SimpleExplicit se1(11);

  Simple s2{11};
  SimpleExplicit se2{11};

  Simple s3 = 11;
  // SimpleExplicit se3 = 11;
  SimpleExplicit se3 = SimpleExplicit(11);

  someFunc<Simple>(11);
  // someFunc<SimpleExplicit>(11);
  someFunc<SimpleExplicit>(SimpleExplicit(11));

  Simple s4 = {};
  someFunc<Simple>({});
  // SimpleExplicit se4 = {};
  SimpleExplicit se4 = SimpleExplicit{};
  // someFunc<SimpleExplicit>({});
  someFunc<SimpleExplicit>(SimpleExplicit{});

  Simple s5 = {11};
  someFunc<Simple>({11});
  // SimpleExplicit se5 = {11};
  SimpleExplicit se5 = SimpleExplicit{11};
  // someFunc<SimpleExplicit>({11});
  someFunc<SimpleExplicit>(SimpleExplicit{11});

  Simple s6 = {11, 22};
  someFunc<Simple>({11, 22});
  // SimpleExplicit se6 = {11, 22};
  SimpleExplicit se6 = SimpleExplicit{11, 22};
  // someFunc<SimpleExplicit>({11, 22});
  someFunc<SimpleExplicit>(SimpleExplicit{11, 22});

  Simple s7{};
  bool b7 = s7;

  SimpleExplicit se7{};
  // bool be7 = se7;
  bool be7 = static_cast<bool>(se7);

  return 0;

}


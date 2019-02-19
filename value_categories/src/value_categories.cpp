
int func(int i) {
  return i + 1;
}

int other_func(int i) {
  return i * 2;
}

using func_type_rvalue_ref = int (&&)(int);
func_type_rvalue_ref return_func() {
  return func;
}

void lvalue_properties() {

  auto* func_ptr = &func;
  auto& func_ref = func;
  // func = other_func; error!

  int&& rrn = int(123);
  auto* pn = &rrn;
  auto& rn = rrn;

  {
    int n = 0;
    auto* pn = &(1, n);
    auto& rn = (1, n);
    1, n = 2;
  }

  auto* p = &"Hello, World!";
  // p[0] = 'P'; error!

  auto* fp = &return_func();
}

int main(int, char**) {

  lvalue_properties();

  return 0;

}


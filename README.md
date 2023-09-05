# Eval for C

Eval.h & EvalString.h is a simple way to evaluate mathematical expressions.

## Installation

Clone this repository

```bash
git clone https://github.com/codingbear314/CEval.git
```
Copy Eval.h & Eval.cpp to your working directory for double & int evaluation,

and copy 4 files in Eval string folder for string evaluation.

## Usage

Eval.h for only int & double evaluation
```cpp
#include "Eval.h"
#include <iostream>
#include <string>

int main()
{
    Eval eval;
    while (true)
    {
        std::string Expression;
        std::cin >> Expression;
        std::cout << Answer : << eval(Expression) << std::endl;
    }
    return 0;
}
```
 
EvalString.h for string evaluation
```cpp
#include "EvalString.h"
#include <iostream>
#include <string>

int main()
{
    expreval::Eval eval;
    while (true)
    {
        std::string Expression;
        std::cin >> Expression;
        std::cout << Answer:;
        expreval::print(eval(Expression));
        std::cout << std::endl;
    }
    return 0;
}
```

## Contributing

Pull requests are welcome. For major changes, please open an issue first
to discuss what you would like to change.

Please make sure to update tests as appropriate.

## License

[MIT](https://choosealicense.com/licenses/mit/)
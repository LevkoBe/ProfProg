### Test Case № 1: Basic Name Entry

**Precondition:** The program is started.

| Step | Expected Output |
| --- | --- |
| Enter `hello John` | `Welcome, John!` |
| Enter `hello John` | `Hello again(x2), John!` |
| Enter `hello John` | `Hello again(x3), John!` |
| Enter `hello John` | Sequence of outputs with consecutive numbers starting from 3 in the format: `Hello again(x<N>), John!` |

### Test Case № 2: Name Deletion

**Precondition:** The program is started.

| Step | Expected Output |
| --- | --- |
| Enter `John delete` | `No history found for John.` |
| Enter `hello John` | `Welcome, John!` |
| Enter `hello John` | `Hello again(x2), John!` |
| Enter `John delete` | `History for John was deleted` |
| Enter `hello John` | `Welcome, John!` |

### Test Case № 3: Secret Word Clearing History

**Precondition:** The program is started.

| Step | Expected Output |
| --- | --- |
| Enter `hello Jane` | `Welcome, Jane!` |
| Enter `hello Jane` | `Hello again(x2), Jane!` |
| Enter `hello bread` | `Secret word was entered. Clearing all the history...` |
| Enter `hello John` | `Welcome, John!` |
| Enter `hello Jane` | `Welcome, Jane!` |

### Test Case № 4: Multiple Name Entries

**Precondition:** The program is started.

| Step | Expected Output |
| --- | --- |
| Enter `hello Alice` | `Welcome, Alice!` |
| Enter `hello Alice` | `Hello again(x2), Alice!` |
| Enter `hello Alice` | `Hello again(x3), Alice!` |
| Enter `hello Bob` | `Welcome, Bob!` |
| Enter `hello Bob` | `Hello again(x2), Bob!` |
| Enter `hello Alice` | `Hello again(x4), Alice!` |
| Enter `hello Bob` | `Hello again(x3), Bob!` |

### Test Case № 5: Name Deletion with Multiple Entries

**Precondition:** The program is started.

| Step | Expected Output |
| --- | --- |
| Enter `hello Mary` | `Welcome, Mary!` |
| Enter `hello Mary` | `Hello again(x2), Mary!` |
| Enter `hello Mary` | `Hello again(x3), Mary!` |
| Enter `Mary delete` | `History for Mary was deleted` |
| Enter `hello Mary` | `Welcome, Mary!` |
| Enter `hello Mary` | `Hello again(x2), Mary!` |
| Enter `Mary delete` | `History for Mary was deleted` |
| Enter `hello bread` | `Secret word was entered. Clearing all the history...` |

### Test Case № 6: Secret Word Clearing History with Multiple Entries

**Precondition:** The program is started.

| Step | Expected Output |
| --- | --- |
| Enter `hello Peter` | `Welcome, Peter!` |
| Enter `hello Peter` | `Hello again(x2), Peter!` |
| Enter `hello Peter` | `Hello again(x3), Peter!` |
| Enter `hello bread` | `Secret word was entered. Clearing all the history...` |
| Enter `hello Peter` | `Welcome, Peter!` |
| Enter `hello Peter` | `Hello again(x2), Peter!` |
| Enter `Peter delete` |  `History for Peter was deleted` |
| Enter `hello Peter` | `Welcome, Peter!` |

### Test Case № 7: Name with Multiple Words

**Precondition:** The program is started.

| Step | Expected Output |
| --- | --- |
| Enter `hello John Smith` | `Welcome, John Smith!` |
| Enter `hello John Smith` | `Hello again(x2), John Smith!` |
| Enter `hello John Smith` | `Hello again(x3), John Smith!` |
| Enter `hello Alice Cooper` | `Welcome, Alice Cooper!` |
| Enter `hello Alice Cooper` | `Hello again(x2), Alice Cooper!` |
| Enter `hello Alice Cooper` | Sequence of outputs with consecutive numbers starting from 3 `Hello again(x3), Alice Cooper!` |

### Test Case № 8: (In)correct Inputs Handling

**Precondition:** The program is started.

| Step | Input | Expected Output |
| --- | --- | --- |
| Enter an invalid input | `xyz` | `Please, enter a valid command (e.g. "hello [username]", or "[username] delete").` |
| Enter a name without the "hello" prefix | `John` | `Please, enter a valid command (e.g. "hello [username]", or "[username] delete").` |
| Enter a name with the "hello" prefix, but with incorrect command | `hello John delete` | `Welcome, John delete!` |
| Enter an input without a space | `helloJohn` | `Hello!` |
| Enter an empty input | `[empty]` | `Please, enter a valid command (e.g. "hello [username]", or "[username] delete").` |
| Enter "hello" without a name | `hello` | `Hello!` |
| Enter "hello " without a name, but with a space | `hello ` | `Please, enter a valid command (e.g. "hello [username]", or "[username] delete").` |

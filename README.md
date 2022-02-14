# 42Seoul Minishell

> **As beautiful as a shell**
> With `Minishell`, you’ll be able to travel through time and come back to problems people faced when `Windows` didn’t exist.

<br>

## About

> minishell 프로젝트의 목표는 간단한 쉘을 만드는 것입니다.

- 새로운 명령어를 입력할 수 있는 프롬프트를 출력합니다.
- 작업 히스토리를 가지고 있습니다.
- PATH 변수나 상대, 절대 경로를 활용하여 올바른 실행 파일을 찾아 실행할 수 있습니다.
- 다음 builtin 명령어들을 실행할 수 있습니다.
  - '-n' 옵션을 사용할 수 있는 `echo` 명령어
  - 상대 또는 절대경로를 사용하는 `cd` 명령어
  - 옵션이 없는 `pwd` 명령어
  - 옵션이 없는 `export` 명령어
  - 옵션이 없는 `unset ` 명령어
  - 옵션과 인자값이 없는 `env` 명령어
  - 옵션이 없는 `exit` 명령어

  이외의 외부 명령어들을 사용할 수 있습니다.
- 리다이렉션과 파이프
  - `<`, `>`, `<<`, `>>` 구분자가 bash처럼 동작합니다.
  - 파이프 `|`가 bash처럼 동작합니다.
- `;`로 명령어를 분리할 수 있습니다.
- `'`와 `"`가 bash처럼 동작합니다. (multiline commands 제외)
- 환경변수(`$` 다음에 문자열이 오는 형식)를 사용할 수 있습니다.
- `$?`는 bash처럼 가장 최근의 종료 상태를 출력합니다.
- `ctrl-C`, `ctrl-D`, `ctrl-\` 가 bash와 동일하게 동작합니다.
  - `ctrl-C`는 새로운 줄에 새로운 프롬프트를 출력합니다.
  - `ctrl-D`는 쉘을 종료합니다.
  - `ctrl-\`는 아무런 동작도 하지 않습니다.

<br>

## Installation & Usage

1. clone this repository

		git clone https://github.com/SejeongMin/minishell
2. `cd` into the root directory and run `make`

		cd minishell
		make

3. run `./minishell` from the project root.


# language
language study integrated repository


# git 명령어
target folder root 에서 git 커맨드 라인으로 실행해서 git repository 통합

https://github.com/jejeongmin/RainerGrimm.git 의 master 브랜치로부터 현재 targget git root directory 에 concurrency_modern_cpp 라는 이름으로 통합
`git subtree add --prefix=concurrency_modern_cpp https://github.com/jejeongmin/RainerGrimm.git master`

위에 실행한 통합을 master 브랜치에 푸쉬
`git push origin HEAD:master`

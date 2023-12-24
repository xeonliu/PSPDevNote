# CI/CD

自动构建 EBOOT.PBP

参考资料：https://github.com/IridescentRose/PSP-GH-Actions-Test/

Using CMake & build yourself.
https://github.com/Iridescence-Technologies/Stardust-Celeste/blob/edge/.github/workflows/stardust.yml

## 关于持续部署

持续部署 (CD) 是使用自动化发布和部署软件更新的做法。 我们希望 Github 在代码更新时自动为我们构建和发布 EBOOT.PBP

## Github Actions

PSPDev 提供了一个已经配置好 PSP 开发环境的 Docker，可以使用 GithubActions 通过 Docker 构建 EBOOT.PBP

```yml
# This is a basic workflow to help you get started with Actions

name: CI

# Controls when the workflow will run
on:
  # Triggers the workflow on push or pull request events but only for the master branch
  push:
    branches: [master]
  pull_request:
    branches: [master]

  # Allows you to run this workflow manually from the Actions tab
  workflow_dispatch:

# A workflow run is made up of one or more jobs that can run sequentially or in parallel
jobs:
  # This workflow contains a single job called "build"
  build:
    # The type of runner that the job will run on
    runs-on: ubuntu-latest
    # Docker Image
    container: pspdev/pspdev:latest

    # Steps represent a sequence of tasks that will be executed as part of the job
    steps:
      - name: Install Dependencies
        run: |
          apk add cmake gmp mpc1 mpfr4 make

      - name: Checkout
        uses: actions/checkout@v2

      - name: Build
        run: |
          make

      - name: Upload a Build Artifact
        uses: actions/upload-artifact@v2.3.0
        with:
          # Artifact name
          name: PSP_Artifact # optional, default is artifact
          # A file, directory or wildcard pattern that describes what to upload
          path: EBOOT.PBP
          if-no-files-found: warn # optional, default is warn
          retention-days: 30 # optional
```

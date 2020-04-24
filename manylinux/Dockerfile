FROM quay.io/pypa/manylinux2010_x86_64
ENV PLAT manylinux2010_x86_64

COPY entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh

ENV CMAKE_VERSION=3.17.1

RUN curl -L https://github.com/Kitware/CMake/releases/download/v${CMAKE_VERSION}/cmake-${CMAKE_VERSION}-Linux-x86_64.tar.gz -o cmake.tar.gz && \
    tar -xzvf cmake.tar.gz

ENTRYPOINT ["/entrypoint.sh"]
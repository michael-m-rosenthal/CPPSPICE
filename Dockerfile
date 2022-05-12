from ubuntu:focal

COPY install_focal_preliminaries.sh /
RUN chmod +x /install_focal_preliminaries.sh
RUN /install_focal_preliminaries.sh

RUN apt-get install wget -y

RUN mkdir -p /CPPSPICE/

WORKDIR /CPPSPICE

COPY download_and_unzip_linux_64_cspice.sh /CPPSPICE/
RUN chmod +x ./download_and_unzip_linux_64_cspice.sh
RUN ./download_and_unzip_linux_64_cspice.sh

WORKDIR /CPPSPICE/cspice
RUN chmod +x makeall.csh; ./makeall.csh

WORKDIR /CPPSPICE

RUN mkdir -p /CPPSPICE/bin
RUN mkdir -p /CPPSPICE/build
RUN mkdir -p /CPPSPICE/cspice/lib
RUN mkdir -p /CPPSPICE/cspice/exe

COPY get_spice_data.sh /CPPSPICE/
RUN chmod +x /CPPSPICE/get_spice_data.sh
RUN ./get_spice_data.sh

COPY get_oldspice_data.sh /CPPSPICE/
RUN chmod +x /CPPSPICE/get_oldspice_data.sh
RUN ./get_oldspice_data.sh

COPY build_cpp.sh /CPPSPICE/
COPY src /CPPSPICE/src

COPY build_cpp.sh /CPPSPICE/
RUN chmod +x /CPPSPICE/build_cpp.sh
RUN ./build_cpp.sh

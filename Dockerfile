from ubuntu:focal

COPY install_focal_preliminaries.sh /
RUN chmod +x /install_focal_preliminaries.sh
RUN /install_focal_preliminaries.sh

RUN apt-get install wget -y

RUN mkdir -p /CPPSPICE/

COPY download_and_unzip_linux_64_cspice.sh /CPPSPICE/
RUN cd /CPPSPICE;chmod +x ./download_and_unzip_linux_64_cspice.sh
RUN cd /CPPSPICE;./download_and_unzip_linux_64_cspice.sh

RUN mkdir -p /CPPSPICE/bin
RUN mkdir -p /CPPSPICE/build
RUN mkdir -p /CPPSPICE/cspice/lib
RUN mkdir -p /CPPSPICE/cspice/exe

RUN cd /CPPSPICE/cspice; chmod +x makeall.csh; ./makeall.csh

COPY get_data.sh /CPPSPICE/
RUN chmod +x /CPPSPICE/get_data.sh
RUN cd /CPPSPICE/; ./get_data.sh

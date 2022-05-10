from ubuntu:focal

COPY install_focal_preliminaries.sh /install_focal_preliminaries.sh
RUN chmod +x /install_focal_preliminaries.sh
RUN /install_focal_preliminaries.sh

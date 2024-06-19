# Build file to create image for django application

FROM alpine:latest
ENV PYTHONDONTWRITEBYTECODE=1
ENV PYTHONUNBUFFERED=1
ENV PORT=8000
WORKDIR /code
COPY ./app/ /code
RUN apk update
RUN apk add --no-cache python3-dev py-pip
RUN apk add --no-cache make automake gcc g++
RUN pip install -r requirements.txt --break-system-packages
RUN pip install tzdata --break-system-packages
ENTRYPOINT python manage.py runserver 0.0.0.0:${PORT} --insecure
EXPOSE ${PORT}
VOLUME /code

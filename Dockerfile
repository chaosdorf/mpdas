FROM alpine

RUN apk --update add build-base libmpdclient-dev curl-dev

WORKDIR /mpdas
COPY ./ ./

RUN make

ENV LASTFM_USERNAME=''
ENV LASTFM_PASSWORD_MD5=''
ENV MPD_SERVER=localhost
ENV MPD_PORT=6600
ENV SERVICE=LastFm
ENV DEBUG=0

CMD ./mpdas

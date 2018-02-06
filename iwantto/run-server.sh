REPOSITORY=martysullivan/twitter-match
TAG=latest

if [ "$1" == "stop" ]
then
    docker rm -f twitter-match 2>&1 > /dev/null
else
    docker login
    docker pull $REPOSITORY:$TAG

    docker run -d \
        --name twitter-match \
        --restart=always \
        -p 80:80 \
        -v $HOME:/root \
        $REPOSITORY:$TAG 2>&1 > /dev/null || \
    docker rm -f twitter-match 2>&1 > /dev/null && \
    docker run -d \
        --name twitter-match \
        --restart=always \
        -p 80:80 \
        -v $HOME:/root \
        $REPOSITORY:$TAG 2>&1 > /dev/null
fi

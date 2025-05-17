FROM mirror.gcr.io/ubuntu:24.04 AS build

RUN --mount=type=cache,target=/var/cache/apt \
    --mount=type=cache,target=/var/lib/apt \
    --mount=type=cache,target=/var/lib/dpkg \
    apt-get update && \
    apt-get install -y --no-install-recommends \
        build-essential \
        cmake

FROM build AS dev

RUN --mount=type=cache,target=/var/cache/apt \
    --mount=type=cache,target=/var/lib/apt \
    --mount=type=cache,target=/var/lib/dpkg \
    apt-get update && \
    apt-get install -y --no-install-recommends \
        git

ARG USER_NAME
ARG GROUP_NAME
ARG USER_ID
ARG GROUP_ID
RUN (userdel -r `id -nu ${USER_ID}` || true) && \
    groupadd -g ${GROUP_ID} ${GROUP_NAME} && \
    useradd -m -u ${USER_ID} -g ${GROUP_NAME} ${USER_NAME} && \
    mkdir /home/${USER_NAME}/.ssh && \
    chown -R ${USER_ID}:${GROUP_ID} /home/${USER_NAME}/.ssh

USER ${USER_NAME}
WORKDIR /home/${USER_NAME}
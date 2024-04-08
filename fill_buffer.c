void fill_buffer(
    const char *dir, size_t dirlen, const char *fname, size_t filelen,
    const char *ext, size_t extlen, char *path
) {

    if (dirlen > 0) {
        memcpy(path, dir, dirlen);
    }
    path[dirlen] = '/';

    if (filelen > 0) {
        memcpy(path + dirlen + 1, fname, filelen);
    }
    path[dirlen + 1 + filelen] = '.';

    if (extlen > 0) {
        memcpy(path + dirlen + 1 + filelen + 1, ext, extlen);
    }

    path[dirlen + 1 + filelen + 1 + extlen] = '\0';
}

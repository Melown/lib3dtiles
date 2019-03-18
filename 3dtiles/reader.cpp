/**
 * Copyright (c) 2019 Melown Technologies SE
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * *  Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "dbglog/dbglog.hpp"

#include "reader.hpp"

namespace fs = boost::filesystem;

namespace threedtiles {

namespace {

namespace constants {
const std::string TilesetJson("tileset.json");
} // namespace constants

inline const fs::path& coalesce(const boost::optional<fs::path> &opt
                                , const fs::path &dflt)
{
    return opt ? *opt : dflt;
}

} // namespace

Archive::Archive(const fs::path &root, const std::string &mime)
    : archive_(root
               , roarchive::OpenOptions().setHint(constants::TilesetJson)
               .setInlineHint('#')
               .setMime(mime))
    , tileset_(tileset(coalesce(archive_.usedHint(), constants::TilesetJson)))
{}

Archive::Archive(roarchive::RoArchive &archive)
    : archive_(archive.applyHint(constants::TilesetJson))
    , tileset_(tileset(constants::TilesetJson))
{
}

roarchive::IStream::pointer Archive::istream(const fs::path &path) const
{
    return archive_.istream(path);
}

Tileset Archive::tileset(const boost::filesystem::path &path) const
{
    Tileset ts;
    read(*istream(path), ts, path);
    return ts;
}

} // namespace threedtiles
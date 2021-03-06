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

#ifndef threedtiles_b3dm_hpp_included_
#define threedtiles_b3dm_hpp_included_

#include <iosfwd>

#include "gltf/gltf.hpp"
#include "gltf/meshloader.hpp"

namespace threedtiles {

struct BatchedModel {
    gltf::Model model;
    math::Point3 rtcCenter;
};

/** Write a glTF archive as a b3dm file.
 */
void b3dm(std::ostream &os, const BatchedModel &model
          , const boost::filesystem::path &srcDir);

/** Write a glTF archive as a b3dm file.
 */
void b3dm(const boost::filesystem::path &path, const BatchedModel &model
          , const boost::filesystem::path &srcDir);

/** Write a glTF archive as a b3dm file.
 */
void b3dm(std::ostream &os, const gltf::Model &model
          , const boost::filesystem::path &srcDir
          , const math::Point3 &rtcCenter = math::Point3());

/** Write a glTF archive as a b3dm file.
 */
void b3dm(const boost::filesystem::path &path, const gltf::Model &model
          , const boost::filesystem::path &srcDir
          , const math::Point3 &rtcCenter = math::Point3());

/** Read a glTF archive from a b3dm file
 */
BatchedModel b3dm(std::istream &is
                  , const boost::filesystem::path &path = "UNKNOWN");

/** Read a glTF archive from a b3dm file
 */
BatchedModel b3dm(const boost::filesystem::path &path);

void loadMesh(gltf::MeshLoader &loader, const BatchedModel &model
              , gltf::MeshLoader::DecodeOptions options);

// inlines

inline void b3dm(std::ostream &os, const BatchedModel &model
                 , const boost::filesystem::path &srcDir)
{
    b3dm(os, model.model, srcDir, model.rtcCenter);
}

inline void b3dm(const boost::filesystem::path &path, const BatchedModel &model
                 , const boost::filesystem::path &srcDir)
{
    b3dm(path, model.model, srcDir, model.rtcCenter);
}

} // namespace threedtiles

#endif // threedtiles_b3dm_hpp_included_

/*
 *  Copyright (c) 2009-2011, NVIDIA Corporation
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *      * Redistributions of source code must retain the above copyright
 *        notice, this list of conditions and the following disclaimer.
 *      * Redistributions in binary form must reproduce the above copyright
 *        notice, this list of conditions and the following disclaimer in the
 *        documentation and/or other materials provided with the distribution.
 *      * Neither the name of NVIDIA Corporation nor the
 *        names of its contributors may be used to endorse or promote products
 *        derived from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 *  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 *  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 *  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 *  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once
#include "io/OctreeFile.hpp"
#include "io/OctreeRuntime.hpp"
#include "render/CudaRenderer.hpp"
#include "build/BuilderBase.hpp"
#include "base/Timer.hpp"
#include "gui/Window.hpp"
#include "gui/Image.hpp"
#include "3d/CameraControls.hpp"

namespace FW
{
//------------------------------------------------------------------------

class BenchmarkContext : public Window::Listener
{
public:
    enum
    {
        MaxPrefetchBytesTotal   = OctreeFile::MaxPrefetchBytesTotal
    };

public:
                        BenchmarkContext    (void);
    virtual             ~BenchmarkContext   (void);

    OctreeFile*         getFile             (void) const                { return m_file; }
    OctreeRuntime*      getRuntime          (void) const                { return m_runtime; }
    CudaRenderer*       getRenderer         (void) const                { return m_renderer; }

    void                setFile             (const String& fileName);
    void                clearRuntime        (void);
    void                load                (int numLevels = OctreeFile::UnitScale);

    void                setCamera           (const String& signature)   { m_camera.decodeSignature(signature); failIfError(); }
    Mat4f               getOctreeToWorld    (int objectID = 0) const;
    Mat4f               getWorldToCamera    (void) const                { return m_camera.getWorldToCamera(); }
    Mat4f               getProjection       (const Vec2i& frameSize) const;
    void                renderOctree        (Image& image, int objectID = 0) const;

    void                setWindowTitle      (const String& title)       { m_window->setTitle(title); }
    void                showImage           (Image& image);
    void                showOctree          (const Vec2i& frameSize, int objectID = 0);
    void                hideWindow          (void);

    virtual bool        handleEvent         (const Window::Event& ev);

    static BuilderBase::Params readBuildParams(const String& stateFile);

private:
                        BenchmarkContext    (const BenchmarkContext&); // forbidden
    BenchmarkContext&   operator=           (const BenchmarkContext&); // forbidden

private:
    OctreeFile*         m_file;
    OctreeRuntime*      m_runtime;
    CudaRenderer*       m_renderer;

    S32                 m_numLevels;

    CameraControls      m_camera;
    Window*             m_window;
    Image*              m_image;
};

//------------------------------------------------------------------------
}
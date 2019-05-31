/*
-----------------------------------------------------------------------------
This source file is part of OGRE
(Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2014 Torus Knot Software Ltd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/
#include "OgreD3D11MultiRenderTarget.h"
#include "OgreD3D11RenderSystem.h"
#include "OgreRoot.h"
#include "OgreD3D11Texture.h"
#include "OgreD3D11HardwarePixelBuffer.h"

namespace Ogre 
{
    //---------------------------------------------------------------------
    D3D11MultiRenderTarget::D3D11MultiRenderTarget(const String &name) :
    //---------------------------------------------------------------------
    MultiRenderTarget(name), mNumberOfViews(0)
    {
        /// Clear targets
        for(size_t x=0; x<OGRE_MAX_MULTIPLE_RENDER_TARGETS; ++x)
        {
            targets[x] = 0;
            mRenderTargetViews[x] = 0;
            mRenderTargets[x] = 0;
        }
    }
    //---------------------------------------------------------------------
    D3D11MultiRenderTarget::~D3D11MultiRenderTarget()
    {
    }
    //---------------------------------------------------------------------
    void D3D11MultiRenderTarget::bindSurfaceImpl(size_t attachment, RenderTexture *target)
    {
        assert(attachment<OGRE_MAX_MULTIPLE_RENDER_TARGETS);
        /// Get buffer and surface to bind to
        D3D11HardwarePixelBuffer *buffer = 0;
        target->getCustomAttribute("BUFFER", &buffer);
        assert(buffer);

        /// Find first non-null target
        int y;
        for(y=0; y<OGRE_MAX_MULTIPLE_RENDER_TARGETS && !mRenderTargets[y]; ++y) ;

        if(y!=OGRE_MAX_MULTIPLE_RENDER_TARGETS)
        {
            /// If there is another target bound, compare sizes
            if(mRenderTargets[y]->getWidth() != target->getWidth() ||
                mRenderTargets[y]->getHeight() != target->getHeight())
            {
				OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS, 
                    "MultiRenderTarget surfaces are not of same size", 
                    "D3D11MultiRenderTarget::bindSurface"
                    );
            }
        }

        targets[attachment] = buffer;
        mRenderTargets[attachment] = target;

        ID3D11RenderTargetView** v;
        target->getCustomAttribute( "ID3D11RenderTargetView", &v );
        mRenderTargetViews[attachment] = *v;

        if(mNumberOfViews < OGRE_MAX_MULTIPLE_RENDER_TARGETS)
            mNumberOfViews++;

        checkAndUpdate();
    }
    //---------------------------------------------------------------------
    void D3D11MultiRenderTarget::unbindSurfaceImpl(size_t attachment)
    {
        assert(attachment<OGRE_MAX_MULTIPLE_RENDER_TARGETS);
        targets[attachment] = 0;
        mRenderTargetViews[attachment] = 0;

        if(mNumberOfViews > 0)
            mNumberOfViews--;

        checkAndUpdate();
    }
    //---------------------------------------------------------------------
    void D3D11MultiRenderTarget::update(void)
    {
        //D3D11RenderSystem* rs = static_cast<D3D11RenderSystem*>(Root::getSingleton().getRenderSystem());

        MultiRenderTarget::update();
    }

    uint D3D11MultiRenderTarget::getNumberOfViews() const { return mNumberOfViews; }

    ID3D11Texture2D* D3D11MultiRenderTarget::getSurface(uint index) const
    {
        D3D11RenderTarget* renderTarget = dynamic_cast<D3D11RenderTarget*>(mRenderTargets[index]);
        return renderTarget ? renderTarget->getSurface() : NULL;
    }

    ID3D11RenderTargetView* D3D11MultiRenderTarget::getRenderTargetView(uint index) const
    {
        D3D11RenderTarget* renderTarget = dynamic_cast<D3D11RenderTarget*>(mRenderTargets[index]);
        return renderTarget ? renderTarget->getRenderTargetView() : NULL;
    }

    //---------------------------------------------------------------------
    void D3D11MultiRenderTarget::getCustomAttribute(const String& name, void *pData)
    {
        if(name == "DDBACKBUFFER")
        {
            ID3D11Texture2D** pSurf = (ID3D11Texture2D**)pData;
            for(unsigned i = 0; i < OGRE_MAX_MULTIPLE_RENDER_TARGETS; ++i)
                pSurf[i] = targets[i] ? targets[i]->getParentTexture()->GetTex2D() : NULL;
        }
        else if(name == "ID3D11RenderTargetView")
        {
            ID3D11RenderTargetView** pRTView = (ID3D11RenderTargetView**)pData;
            memset(pRTView, 0, OGRE_MAX_MULTIPLE_RENDER_TARGETS * sizeof(ID3D11RenderTargetView*));
            for(unsigned i = 0; i < OGRE_MAX_MULTIPLE_RENDER_TARGETS && mRenderTargets[i]; ++i)
                mRenderTargets[i]->getCustomAttribute("ID3D11RenderTargetView", &pRTView[i]);
        }
        else if( name == "numberOfViews" )
        {
            *(unsigned*)pData = mNumberOfViews;
        }
        else if(name == "isTexture")
        {
            *(bool*)pData = false;
        }
        else
            MultiRenderTarget::getCustomAttribute(name, pData);
    }
    //---------------------------------------------------------------------
    void D3D11MultiRenderTarget::checkAndUpdate()
    {
        if(mRenderTargets[0])
        {
            mWidth = static_cast<unsigned int>(mRenderTargets[0]->getWidth());
            mHeight = static_cast<unsigned int>(mRenderTargets[0]->getHeight());
        }
        else
        {
            mWidth = 0;
            mHeight = 0;
        }
    }
    //---------------------------------------------------------------------


}


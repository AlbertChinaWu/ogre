/*
-----------------------------------------------------------------------------
This source file is part of OGRE
(Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org

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
#ifndef _ShaderCookTorranceLighting_
#define _ShaderCookTorranceLighting_

#include "OgreShaderPrerequisites.h"
#ifdef RTSHADER_SYSTEM_BUILD_EXT_SHADERS
#include "OgreShaderFFPLighting.h"
#include "OgreLight.h"
#include "OgreCommon.h"

namespace Ogre {
namespace RTShader {

/** \addtogroup Optional
*  @{
*/
/** \addtogroup RTShader
*  @{
*/

/** Per pixel Lighting extension sub render state implementation.
Derives from SubRenderState class.
*/
class _OgreRTSSExport CookTorranceLighting : public NormalMapLighting
{

// Interface.
public:
    /**
    @see SubRenderState::getType.
    */
    virtual const String& getType() const;

    virtual void updateGpuProgramsParams(Renderable* rend, const Pass* pass, const AutoParamDataSource* source, const LightList* pLightList);

    static String Type;

// Protected methods
protected:
    /**
    @see SubRenderState::resolveParameters.
    */
    virtual bool resolveParameters(ProgramSet* programSet);

    /** Resolve global lighting parameters */
    virtual bool resolveGlobalParameters(ProgramSet* programSet);

    /**
    @see SubRenderState::resolveDependencies.
    */
    virtual bool resolveDependencies(ProgramSet* programSet);

    /**
    @see SubRenderState::addFunctionInvocations.
    */
    virtual bool addFunctionInvocations(ProgramSet* programSet);

    void addPSIlluminationInvocation(const LightParams* curLightParams, const FunctionStageRef& stage);

// Attributes.
protected:
    UniformParameterPtr mSurfaceDiffuseColour;
    UniformParameterPtr mSurfaceRoughness;
    UniformParameterPtr mSurfaceMetallness;
};


/**
A factory that enables creation of PerPixelLighting instances.
@remarks Sub class of SubRenderStateFactory
*/
class _OgreRTSSExport CookTorranceLightingFactory : public SubRenderStateFactory
{
public:

    /**
    @see SubRenderStateFactory::getType.
    */
    virtual const String& getType() const;

    /**
    @see SubRenderStateFactory::createInstance.
    */
    virtual SubRenderState* createInstance(ScriptCompiler* compiler, PropertyAbstractNode* prop, Pass* pass, SGScriptTranslator* translator);

    /**
    @see SubRenderStateFactory::writeInstance.
    */
    virtual void writeInstance(MaterialSerializer* ser, SubRenderState* subRenderState, Pass* srcPass, Pass* dstPass);


protected:

    /**
    @see SubRenderStateFactory::createInstanceImpl.
    */
    virtual SubRenderState* createInstanceImpl();


};

/** @} */
/** @} */

}
}

#endif
#endif

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
#ifndef __BillboardParticleRenderer2_H__
#define __BillboardParticleRenderer2_H__

#include <memory>
#include "OgrePrerequisites.h"
#include "OgreParticleSystemRenderer2.h"
#include "OgreBillboardSet.h"
#include "OgreHeaderPrefix.h"

namespace Ogre {

    /** \addtogroup Core
    *  @{
    */
    /** \addtogroup Effects
    *  @{
    */

    /** Specialisation of ParticleSystemRenderer to render particles using 
        a BillboardSet. 
    @remarks
        This renderer has a few more options than the standard particle system,
        which will be passed to it automatically when the particle system itself
        does not understand them.
    */
    class BillboardParticleRenderer : public ParticleSystemRenderer
    {
    protected:
        /// The billboard set that's doing the rendering
        BillboardSet* mBillboardSet;
        BillboardParticleRenderer();
    public:
        ~BillboardParticleRenderer();

        virtual ParticleSystemRenderer::Ptr clone () override;
        static ParticleSystemRenderer::Ptr create ();

        /** Command object for billboard type (see ParamCommand).*/
        class _OgrePrivate CmdBillboardType : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };
        /** Command object for billboard origin (see ParamCommand).*/
        class _OgrePrivate CmdBillboardOrigin : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };
        /** Command object for billboard rotation type (see ParamCommand).*/
        class _OgrePrivate CmdBillboardRotationType : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };
        /** Command object for common direction (see ParamCommand).*/
        class _OgrePrivate CmdCommonDirection : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };
        /** Command object for common up-vector (see ParamCommand).*/
        class _OgrePrivate CmdCommonUpVector : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };
        /** Command object for point rendering (see ParamCommand).*/
        class _OgrePrivate CmdPointRendering : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };
        /** Command object for accurate facing(see ParamCommand).*/
        class _OgrePrivate CmdAccurateFacing : public ParamCommand
        {
        public:
            String doGet(const void* target) const;
            void doSet(void* target, const String& val);
        };

        /// @copydoc BillboardSet::setBillboardType
        void setBillboardType(BillboardType bbt) { mBillboardSet->setBillboardType(bbt); }
        /// @copydoc BillboardSet::getBillboardType
        BillboardType getBillboardType(void) const { return mBillboardSet->getBillboardType(); }
        /// @copydoc BillboardSet::setUseAccurateFacing
        void setUseAccurateFacing(bool acc) { mBillboardSet->setUseAccurateFacing(acc); }
        /// @copydoc BillboardSet::getUseAccurateFacing
        bool getUseAccurateFacing(void) const { return mBillboardSet->getUseAccurateFacing(); }
        /// @copydoc BillboardSet::setBillboardOrigin
        void setBillboardOrigin(BillboardOrigin origin) { mBillboardSet->setBillboardOrigin(origin); }
        /// @copydoc BillboardSet::getBillboardOrigin
        BillboardOrigin getBillboardOrigin(void) const { return mBillboardSet->getBillboardOrigin(); }
        /// @copydoc BillboardSet::setBillboardRotationType
        void setBillboardRotationType(BillboardRotationType rotationType)
        {
            mBillboardSet->setBillboardRotationType(rotationType);
        }
        /// @copydoc BillboardSet::getBillboardRotationType
        BillboardRotationType getBillboardRotationType() const
        {
            return mBillboardSet->getBillboardRotationType();
        }
        /// @copydoc BillboardSet::setCommonDirection
        void setCommonDirection(const Vector3& vec) { mBillboardSet->setCommonDirection(vec); }
        /// @copydoc BillboardSet::getCommonDirection
        const Vector3& getCommonDirection(void) const { return mBillboardSet->getCommonDirection(); }
        /// @copydoc BillboardSet::setCommonUpVector
        void setCommonUpVector(const Vector3& vec) { mBillboardSet->setCommonUpVector(vec); }
        /// @copydoc BillboardSet::getCommonUpVector
        const Vector3& getCommonUpVector(void) const { return mBillboardSet->getCommonUpVector(); }
        /// @copydoc BillboardSet::setPointRenderingEnabled
        void setPointRenderingEnabled(bool enabled) { mBillboardSet->setPointRenderingEnabled(enabled); }
        /// @copydoc BillboardSet::isPointRenderingEnabled
        bool isPointRenderingEnabled(void) const { return mBillboardSet->isPointRenderingEnabled(); }

        /// @copydoc ParticleSystemRenderer::getType
        const String& getType(void) const;
        /// @copydoc ParticleSystemRenderer::_updateRenderQueue
        void _updateRenderQueue(RenderQueue* queue, 
            std::list<Particle2*>& currentParticles, bool cullIndividually);
        virtual void _updateRenderQueue (RenderQueue* queue,
            Particles2& particles, bool cullIndividually) override;
        /// @copydoc ParticleSystemRenderer::visitRenderables
        void visitRenderables(Renderable::Visitor* visitor, bool debugRenderables = false)
        {
            mBillboardSet->visitRenderables(visitor, debugRenderables);
        }
        void _setMaterial(MaterialPtr& mat) { mBillboardSet->setMaterial(mat); }
        /// @copydoc ParticleSystemRenderer::_notifyCurrentCamera
        void _notifyCurrentCamera(Camera* cam) { mBillboardSet->_notifyCurrentCamera(cam); }
        /// @copydoc ParticleSystemRenderer::_notifyParticleQuota
        void _notifyParticleQuota(size_t quota) { mBillboardSet->setPoolSize(quota); }
        /// @copydoc ParticleSystemRenderer::_notifyAttached
        void _notifyAttached(Node* parent, bool isTagPoint = false)
        {
            mBillboardSet->_notifyAttached(parent, isTagPoint);
        }
        /// @copydoc ParticleSystemRenderer::_notifyDefaultDimensions
        void _notifyDefaultDimensions(Real width, Real height)
        {
            mBillboardSet->setDefaultDimensions(width, height);
        }
        /// @copydoc ParticleSystemRenderer::setRenderQueueGroup
        void setRenderQueueGroup(uint8 queueID) { mBillboardSet->setRenderQueueGroup(queueID); }
        /// @copydoc MovableObject::setRenderQueueGroupAndPriority
        void setRenderQueueGroupAndPriority(uint8 queueID, ushort priority)
        {
            mBillboardSet->setRenderQueueGroupAndPriority(queueID, priority);
        }
        /// @copydoc ParticleSystemRenderer::setKeepParticlesInLocalSpace
        void setKeepParticlesInLocalSpace(bool keepLocal)
        {
            mBillboardSet->setBillboardsInWorldSpace(!keepLocal);
        }
        /// @copydoc ParticleSystemRenderer::_getSortMode
        SortMode _getSortMode(void) const { return mBillboardSet->_getSortMode(); }

        /// Access BillboardSet in use
        BillboardSet* getBillboardSet(void) const { return mBillboardSet; }

    protected:
        static CmdBillboardType msBillboardTypeCmd;
        static CmdBillboardOrigin msBillboardOriginCmd;
        static CmdBillboardRotationType msBillboardRotationTypeCmd;
        static CmdCommonDirection msCommonDirectionCmd;
        static CmdCommonUpVector msCommonUpVectorCmd;
        static CmdPointRendering msPointRenderingCmd;
        static CmdAccurateFacing msAccurateFacingCmd;
    };

    /** Factory class for BillboardParticleRenderer */
/*
    class BillboardParticleRendererFactory2 : public ParticleSystemRendererFactory2
    {
    public:
        /// @copydoc FactoryObj::getType
        const String& getType() const;
        /// @copydoc FactoryObj::createInstance
        ParticleSystemRenderer* createInstance( const String& name );
        /// @copydoc FactoryObj::destroyInstance
        void destroyInstance(ParticleSystemRenderer* ptr);
    };
    */
    /** @} */
    /** @} */

} // namespace Ogre

#include "OgreHeaderSuffix.h"

#endif // __BillboardParticleRenderer_H__


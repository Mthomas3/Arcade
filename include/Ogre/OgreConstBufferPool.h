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
#ifndef _OgreConstBufferPool_H_
#define _OgreConstBufferPool_H_

#include "OgrePrerequisites.h"
#include "Vao/OgreBufferPacked.h"
#include "OgreHeaderPrefix.h"

namespace Ogre
{
    /** \addtogroup Core
    *  @{
    */
    /** \addtogroup Resources
    *  @{
    */

    class ConstBufferPoolUser;

    /** Maintains a pool of buffers grouped by hash ID. Keeping them separated
        by hash prevents mixing materials in the same buffer (which has limited
        space) that could never be batched together in the same draw call.

        When a buffer is full and has used all of its free slots, a new buffer
        is allocated.
    */
    class _OgreExport ConstBufferPool
    {
    public:
        struct BufferPool
        {
            uint32                  hash;
            vector<uint32>::type    freeSlots;
            ConstBufferPacked       *materialBuffer;
            BufferPacked            *extraBuffer;

            BufferPool( uint32 _hash, uint32 slotsPerPool, ConstBufferPacked *_materialBuffer,
                        BufferPacked *_extraBuffer );
        };

        struct _OgreExport ExtraBufferParams
        {
            size_t      bytesPerSlot;
            BufferType  bufferType;
            bool        useTextureBuffers;

            ExtraBufferParams( size_t _bytesPerSlot = 0, BufferType _bufferType = BT_DEFAULT,
                               bool _useTextureBuffers = true );
        };

    protected:
        typedef vector<BufferPool*>::type           BufferPoolVec;
        typedef map<uint32, BufferPoolVec>::type    BufferPoolVecMap;

        typedef vector<ConstBufferPoolUser*>::type  ConstBufferPoolUserVec;

        BufferPoolVecMap    mPools;
        uint32              mBytesPerSlot;
        uint32              mSlotsPerPool;
        size_t              mBufferSize;
        ExtraBufferParams   mExtraBufferParams;
    private:
        VaoManager          *_mVaoManager;
    protected:

        ConstBufferPoolUserVec mDirtyUsers;
        ConstBufferPoolUserVec mUsers;

        void destroyAllPools(void);

        void uploadDirtyDatablocks(void);

    public:
        ConstBufferPool( uint32 bytesPerSlot, const ExtraBufferParams &extraBufferParams );
        virtual ~ConstBufferPool();

        /// Requests a slot and fills 'user'. Automatically schedules for update
        void requestSlot( uint32 hash, ConstBufferPoolUser *user, bool wantsExtraBuffer );
        /// Releases a slot requested with requestSlot.
        void releaseSlot( ConstBufferPoolUser *user );

        void scheduleForUpdate( ConstBufferPoolUser *dirtyUser );

        virtual void _changeRenderSystem( RenderSystem *newRs );
    };

    class _OgreExport ConstBufferPoolUser
    {
        friend class ConstBufferPool;
    protected:

        friend bool OrderConstBufferPoolUserByPoolThenSlot( const ConstBufferPoolUser *_l,
                                                            const ConstBufferPoolUser *_r );

        uint32                      mAssignedSlot;
        ConstBufferPool::BufferPool *mAssignedPool;
        size_t                      mGlobalIndex;
        //ConstBufferPool             *mPoolOwner;
        bool                        mDirty;

        /// Derived class must fill dstPtr. Amount of bytes written can't
        /// exceed the value passed to ConstBufferPool::uploadDirtyDatablocks
        virtual void uploadToConstBuffer( char *dstPtr ) = 0;
        virtual void uploadToExtraBuffer( char *dstPtr ) {}

    public:
        ConstBufferPoolUser();

        uint32 getAssignedSlot(void) const                              { return mAssignedSlot; }
        const ConstBufferPool::BufferPool* getAssignedPool(void) const  { return mAssignedPool; }
    };

    inline bool OrderConstBufferPoolUserByPoolThenSlot( const ConstBufferPoolUser *_l,
                                                        const ConstBufferPoolUser *_r )
    {
        return _l->mAssignedPool < _r->mAssignedPool && _l->mAssignedSlot < _r->mAssignedSlot;
    }

    /** @} */
    /** @} */

}

#include "OgreHeaderSuffix.h"

#endif

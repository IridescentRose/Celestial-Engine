/**
 * Packets
 */
#pragma once
#include "cpch.hpp"

namespace Celeste::Network {

    #define KiB * 1024
    #define MAX_STRING_SIZE (512 KiB)

    /*
        Based off of https://github.com/cuberite/cuberite/blob/master/src/ByteBuffer.h
     */
    class ByteBuffer : public NonCopyable {
    public:
        ByteBuffer(size_t a_BufferSize);
        ~ByteBuffer();

        /** Writes the bytes specified to the ringbuffer. Returns true if successful, false if not */
        bool Write(const void* a_Bytes, size_t a_Count);

#ifdef GetFreeSpace
#undef GetFreeSpace
#endif
        /** Returns the number of bytes that can be successfully written to the ringbuffer */
        [[nodiscard]] size_t GetFreeSpace(void) const;

        /** Returns the number of bytes that are currently in the ringbuffer. Note GetReadableBytes() */
        [[nodiscard]] size_t GetUsedSpace(void) const;

        /** Returns the number of bytes that are currently available for reading (may be less than UsedSpace due to some data having been read already) */
        [[nodiscard]] size_t GetReadableSpace(void) const;

        /** Returns the current data start index. For debugging purposes. */
        [[nodiscard]] size_t GetDataStart(void) const { return m_DataStart; }

        /** Returns true if the specified amount of bytes are available for reading */
        [[nodiscard]] bool CanReadBytes(size_t a_Count) const;

        /** Returns true if the specified amount of bytes are available for writing */
        [[nodiscard]] bool CanWriteBytes(size_t a_Count) const;

        bool WriteBEInt8(int8_t   a_Value);
        bool WriteBEInt16(int16_t  a_Value);
        bool WriteBEInt32(int32_t  a_Value);
        bool WriteBEInt64(int64_t  a_Value);
        bool WriteBEUInt8(uint8_t  a_Value);
        bool WriteBEUInt16(uint16_t a_Value);
        bool WriteBEUInt32(uint32_t a_Value);
        bool WriteBEUInt64(uint64_t a_Value);
        bool WriteBEFloat(float  a_Value);
        bool WriteBEDouble(double a_Value);
        bool WriteBool(bool   a_Value);
        bool WriteVarInt32(uint32_t a_Value);
        bool WriteVarInt64(uint64_t a_Value);
        bool WriteVarUTF8String(std::string& a_Value);

        bool ReadBEInt8(int8_t&   a_Value);
        bool ReadBEInt16(int16_t&  a_Value);
        bool ReadBEInt32(int32_t&  a_Value);
        bool ReadBEInt64(int64_t&  a_Value);
        bool ReadBEUInt8(uint8_t&  a_Value);
        bool ReadBEUInt16(uint16_t& a_Value);
        bool ReadBEUInt32(uint32_t& a_Value);
        bool ReadBEUInt64(uint64_t& a_Value);
        bool ReadBEFloat(float&  a_Value);
        bool ReadBEDouble(double& a_Value);
        bool ReadBool(bool&   a_Value);
        bool ReadVarInt32(uint32_t& a_Value);
        bool ReadVarInt64(uint64_t& a_Value);
        bool ReadLEInt32(int32_t& a_Value);
        bool ReadVarUTF8String(std::string& a_Value);

        /** Reads a_Count bytes into a_Buffer; returns true if successful */
        bool ReadBuf(void* a_Buffer, size_t a_Count);

        /** Writes a_Count bytes into a_Buffer; returns true if successful */
        bool WriteBuf(const void* a_Buffer, size_t a_Count);

        /** Reads a_Count bytes into a_String; returns true if successful */
        bool ReadString(std::string& a_String, size_t a_Count);

        /** Skips reading by a_Count bytes; returns false if not enough bytes in the ringbuffer */
        bool SkipRead(size_t a_Count);

        /** Reads all available data into a_Data */
        void ReadAll(std::string& a_Data);

        /** Reads the specified number of bytes and writes it into the destinatio bytebuffer. Returns true on success. */
        bool ReadToByteBuffer(ByteBuffer& a_Dst, size_t a_NumBytes);

        /** Removes the bytes that have been read from the ringbuffer */
        void CommitRead();

        /** Restarts next reading operation at the start of the ringbuffer */
        void ResetRead();

        /** Re-reads the data that has been read since the last commit to the current readpos. Used by ProtoProxy to duplicate communication */
        void ReadAgain(std::string& a_Out);

        /** Checks if the internal state is valid (read and write positions in the correct bounds) using ASSERTs */
        void CheckValid() const;

        /** Gets the number of bytes that are needed to represent the given VarInt */
        static size_t GetVarIntSize(uint32_t a_Value);

        template <typename T> bool ReadVarInt(T& a_Value)
        {
            uint64_t v;
            bool res = ReadVarInt64(v);
            if (res)
            {
                a_Value = static_cast<T>(v);
            }
            return res;
        }

        char* m_Buffer;
    protected:
        size_t m_BufferSize;  // Total size of the ringbuffer

        size_t m_DataStart;  // Where the data starts in the ringbuffer
        size_t m_WritePos;   // Where the data ends in the ringbuffer
        size_t m_ReadPos;    // Where the next read will start in the ringbuffer

        /** Advances the m_ReadPos by a_Count bytes */
        void AdvanceReadPos(size_t a_Count);
    };

    typedef char byte;

    /**
	 * Packet Output structure.
	 * Requires an ID.
	 *
	 * Packet Output should always be a heap allocated pointer...
	 * This should be gotten by new PacketOut(size) where size is the estimated total size of the packet.
	 * It is always better to be more liberal with this sizing as the send process truncates this.
	 *
	 * Your data should be written onto a ByteBuffer object (buffer).
	 * Upon being sent through the driver interface this packet is deleted.
	**/
    struct PacketOut : public NonCopyable{
        PacketOut(size_t size): ID(0) {
            buffer = new ByteBuffer(size);
        }
        u32 ID;
        ByteBuffer* buffer;
    };

    /**
	 * You will not manually construct a PacketIn - as it is read by Recv.
	 * Packets received will always have an ID and its data stored in the ByteBuffer.
	**/
    struct PacketIn : public NonCopyable{
        PacketIn(size_t size): ID(0) {
            buffer = new ByteBuffer(size);
        }
        u32 ID;
        ByteBuffer* buffer;
    };
}
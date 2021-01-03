from libc.stdint cimport uint16_t, uint32_t, uint64_t
from libcpp cimport bool
from libcpp.vector cimport vector

from .vectors cimport CDVec2
from .exceptions cimport raise_py_error


cdef extern from "kaacore/sprites.h" namespace "kaacore" nogil:
    cdef cppclass CSprite "kaacore::Sprite":
        CDVec2 origin
        CDVec2 dimensions

        CSprite()

        @staticmethod
        CSprite load(const char* path, uint64_t flags) \
            except +raise_py_error

        bool operator==(const CSprite&)

        CSprite crop(CDVec2 new_origin, CDVec2 new_dimensions) \
            except +raise_py_error
        bint has_texture() \
            except +raise_py_error
        CDVec2 get_size() \
            except +raise_py_error

    vector[CSprite] c_split_spritesheet "kaacore::split_spritesheet"(
        const CSprite& spritesheet, const CDVec2 frame_dimensions,
        const size_t frames_offset, const size_t frames_count,
        const CDVec2 frame_padding
    ) except +raise_py_error

#pragma once

// signed integers
using i8 = signed char;
using i16 = signed short;
using i32 = signed int;
using i64 = signed long;

// unsigned integers
using u8 = unsigned char;
using u16 = unsigned short;
using u32 = unsigned int;
using u64 = unsigned long;

// floating point numbers
using f32 = float;
using f64 = double;

// character
using c8 = char;

static_assert(sizeof(i8) == 1, "i8 should have a length of 1 byte.\n");
static_assert(sizeof(i16) == 2, "i16 should have a length of 2 bytes.\n");
static_assert(sizeof(i32) == 4, "i32 should have a length of 4 bytes.\n");
static_assert(sizeof(i64) == 8, "i8 should have a length of 8 bytes.\n");

static_assert(sizeof(u8) == 1, "u8 should have a length of 1 byte.\n");
static_assert(sizeof(u16) == 2, "u16 should have a length of 2 bytes.\n");
static_assert(sizeof(u32) == 4, "u32 should have a length of 4 bytes.\n");
static_assert(sizeof(u64) == 8, "u8 should have a length of 8 bytes.\n");

static_assert(sizeof(f32) == 4, "f32 should have a length of 4 bytes.\n");
static_assert(sizeof(f64) == 8, "f64 should have a length of 8 bytes.\n");

static_assert(sizeof(c8) == 1, "c8 should have a length of 1 byte.\n");

// hi palegrass
#pragma once

class noncopyable {
   protected:
    noncopyable() = default;
    virtual ~noncopyable() = default;

   private:
    noncopyable(const noncopyable &) = delete;
    noncopyable &operator=(const noncopyable &) = delete;
};
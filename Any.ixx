module;

export module ANY;
import <typeinfo>;
import <exception>;
import <algorithm>;

export enum class OwnerShip
{
	Owner,
	Observer
};

struct base
{
    virtual void* to_void_ptr() const& noexcept = 0;
    virtual base* clone() const& = 0;
    virtual ~base() = default;
};

template<typename T>
struct derived final : base
{
    T value;
    derived(T&& value) : value(std::forward<T>(value)) {}
    derived(const T& value) : value(value) {}
    void* to_void_ptr() const& noexcept override
    {
        return reinterpret_cast<void*>(const_cast<T*>(&value));
    }
    base* clone() const& override
    {
        return new derived<T>(value);
    }
};

export template <OwnerShip ownership>
struct Any;

export template <typename T>
concept is_owner = std::is_same_v<typename std::remove_cvref_t<T>::any, Any<OwnerShip::Owner>>;

export template <typename T>
concept is_observer = std::is_same_v<typename std::remove_cvref_t<T>::any, Any<OwnerShip::Observer>>;

export template <typename T>
concept is_interface = std::is_same_v<std::remove_cvref_t<T>, Any<OwnerShip::Owner>> || std::is_same_v<std::remove_cvref_t<T>, Any<OwnerShip::Observer>>;

export template <>
struct Any<OwnerShip::Owner>//这个Any管理内存，有所有权
{
    base* content;
    using any = Any<OwnerShip::Owner>;
    template<typename T>
        requires (!is_interface<T>)
    Any(T&& value) :
        content(new derived<std::decay_t<T>>(std::forward<T>(value)))
    {}
    template<typename T>
    	requires (!is_interface<T>)
    Any(const T& value) :
        content(new derived<std::decay_t<T>>(value))
    {}
    Any() : content(nullptr) {}
    Any(const Any& other)
    {
        if (content)
            delete content;
        if (other.content)
            content = other.content->clone();
    }
    Any(Any&& other) noexcept
    {
        if (content)
            delete content;
        content = std::exchange(other.content, nullptr);
    }
    Any& operator=(const Any& other)
    {
        if (this == &other)
            return *this;
        if (content)
            delete content;
        if (other.content)
            content = other.content->clone();
        return *this;
    }
    Any& operator=(Any&& other) noexcept
    {
        if (this == &other)
            return *this;
        if (content)
            delete content;
        content = std::exchange(other.content, nullptr);
        return *this;
    }
    explicit operator bool() const
    {
        return content != nullptr;
    }
    operator void* () const noexcept
    {
        return content ? content->to_void_ptr() : nullptr;
    }
    template <typename T>
    friend std::decay_t<T>& as(Any<OwnerShip::Owner>& self) noexcept//self为左值就拷贝，右值就移动
    {
        using NonRef = std::decay_t<T>;
        return static_cast<derived<NonRef>*>(self.content)->value;
    }
    template<typename T>
    friend std::decay_t<T> as(Any<OwnerShip::Owner>&& self) noexcept
    {
        using NonRef = std::decay_t<T>;
        auto& temp = static_cast<derived<NonRef>*>(self.content)->value;
        self.content = nullptr;
        return temp;
    }
    ~Any()
    {
        if (content)
            delete content;
        content = nullptr;
    }
};

export template <>
struct Any<OwnerShip::Observer>//这个Any不管理内存，只是一个类型安全的指针，没有所有权
{
    void* content;
    using any = Any<OwnerShip::Observer>;
    Any() = default;
    template<typename T>
		requires (!is_interface<T>)
    Any(T& value) noexcept: content(&value) {}
    template<typename T>//T不能为右值引用
        requires std::is_rvalue_reference_v<T>
    Any(T&& value) = delete;
    Any(const Any& other) = default;
    Any& operator=(const Any& other) = default;
    Any(Any&& other) = delete;
    Any(const Any<OwnerShip::Owner>& owener) noexcept :
        content(static_cast<void*>(owener.content))
	{}
    Any(Any<OwnerShip::Owner>&& owener) = delete;
    Any& operator=(const Any<OwnerShip::Owner>& owener) noexcept
	{
		content = static_cast<void*>(owener.content);
		return *this;
	}
    Any& operator=(Any<OwnerShip::Owner>&& owener) = delete;
    explicit operator bool() const
	{
		return content != nullptr;
	}
    explicit operator void* () const noexcept
    {
        return content;
    }
    template<typename T>
    friend std::decay_t<T>& as(Any<OwnerShip::Observer>& any)
    {
        using NonRef = std::decay_t<T>;// 确保我们处理T类型而不是T&（引用类型）
        return *static_cast<NonRef*>(any.content);
    }
    ~Any() {};
};

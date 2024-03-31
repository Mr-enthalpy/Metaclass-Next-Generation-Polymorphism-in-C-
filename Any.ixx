export module ANY;
import <typeinfo>;
import <exception>;
export class Any//���Any�������ڴ棬ֻ��һ�����Ͱ�ȫ��ָ�룬û������Ȩ
{
private:
    void* content;
    const std::type_info* type_info;
public:
    Any() = default;
    template<typename T>
    Any(T& value) noexcept: content(&value), type_info(&typeid(std::decay_t<T>)) {}
    Any(const Any& other) = default;
    Any& operator=(const Any& other) = default;
    template<typename T>
    friend T& Any_cast(Any& any)
    {
        // ȷ�����Ǵ���T���Ͷ�����T&���������ͣ�
        using NonRef = std::decay_t<T>;
        if (any.type_info != &typeid(NonRef))
            throw std::bad_cast();
        return *static_cast<NonRef*>(any.content);
    }
    explicit operator bool() const
	{
		return content != nullptr;
	}
    const std::type_info& type() const
    {
        return *type_info;
    }
protected:
    virtual ~Any() {};
};
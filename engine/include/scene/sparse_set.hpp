#pragma once

#include <cstddef>
#include <cstdint>

#include <memory>
#include <vector>

namespace engine
{

[[nodiscard]] static size_t fast_mod(const size_t index, const size_t ceil) noexcept;

class sparse_set
{
  protected:
    /** maximum size of sparse or the maximum value in the set */
    static constexpr auto max_size = static_cast<uint32_t>(UINT32_MAX);

    /** maximum number of entries per page */
    static constexpr auto page_size = static_cast<uint8_t>(UINT8_MAX);

    /** sparse array of pages containing indices into packed */
    std::vector<std::shared_ptr<std::vector<uint32_t>>> sparse;

    /** packed array of elements */
    std::vector<uint32_t> packed;

  public:
    using iterator = typename std::vector<uint32_t>::const_iterator;
    using const_iterator = typename std::vector<uint32_t>::const_iterator;

    // clang-format off
    iterator       begin()        { return packed.begin(); }
    iterator       end()          { return packed.begin() + packed.size(); }
    const_iterator begin() const  { return packed.begin(); }
    const_iterator end()   const  { return packed.begin() + packed.size(); }
    // clang-format on

    [[nodiscard]] auto capacity() const noexcept
    {
        return packed.capacity();
    }

    [[nodiscard]] auto size() const noexcept
    {
        return packed.size();
    }

    virtual ~sparse_set() = default;

  private:
    [[nodiscard]] auto entity_to_pos(uint32_t const entity) const noexcept
    {
        return static_cast<size_t>(entity);
    }

    [[nodiscard]] auto pos_to_page(size_t const pos) const noexcept
    {
        return static_cast<size_t>(pos / page_size);
    }

  public:
    [[nodiscard]] auto &search(uint32_t const entity) const noexcept
    {
        auto pos = entity_to_pos(entity);
        auto page = pos_to_page(pos);

        if (!(page < sparse.size()))
        {
            return const_cast<uint32_t &>(null);
        }

        if (!sparse[page])
        {
            return const_cast<uint32_t &>(null);
        }

        auto &index = (*(sparse[page]))[fast_mod(pos, page_size)];

        if (index < size() && packed[index] == entity)
        {
            return index;
        }

        return const_cast<uint32_t &>(null);
    }

  private:
    [[nodiscard]] auto &assure_at_least(uint32_t const entity)
    {
        auto pos = entity_to_pos(entity);
        auto page = pos_to_page(pos);

        if (!(page < sparse.size()))
        {
            sparse.resize(pos + 1u, nullptr);
        }

        if (!sparse[page])
        {
            sparse[page] = std::make_shared<std::vector<uint32_t>>(page_size, null);
        }

        return (*(sparse[page]))[fast_mod(pos, page_size)];
    }

  public:
    void emplace(uint32_t const entity)
    {
        if (entity == null)
        {
            return;
        }

        auto &elem = assure_at_least(entity);
        auto  pos = size();

        if (!(search(entity) == null))
        {
            return;
        }

        packed.push_back(entity);

        elem = static_cast<std::uint32_t>(pos);
    }

    void remove(uint32_t const entity)
    {
        auto &elem = search(entity);

        if (elem == null)
        {
            return;
        }

        auto &back = packed.back();
        auto &last = search(back);

        packed[elem] = back;

        last = elem;
        elem = max_size;

        packed.pop_back();
    }

    auto join(sparse_set const &set)
    {
        sparse_set result;

        for (size_t i = 0; i < size(); i++)
        {
            result.emplace(packed[i]);
        }

        for (size_t i = 0; i < set.size(); i++)
        {
            result.emplace(set.packed[i]);
        }

        return result;
    }

    auto intersect(sparse_set const &set)
    {
        sparse_set result;

        if (size() < set.size())
        {
            for (size_t i = 0; i < size(); i++)
            {
                if (set.search(packed[i]) != max_size)
                {
                    result.emplace(packed[i]);
                }
            }
        }
        else
        {
            for (size_t i = 0; i < set.size(); i++)
            {
                if (search(set.packed[i]) != max_size)
                {
                    result.emplace(set.packed[i]);
                }
            }
        }

        return result;
    }

    static constexpr uint32_t null = UINT32_MAX;
};

[[nodiscard]] static size_t fast_mod(const size_t index, const size_t ceil) noexcept
{
    return index >= ceil ? index % ceil : index;
}

} // namespace engine
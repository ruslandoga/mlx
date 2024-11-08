defmodule MLX do
  @moduledoc "MLX bindings for Elixir"

  @doc """
  Returns the version of the linked MLX library.

      iex> MLX.library_version()
      "v0.18.0"

  """
  @spec library_version :: String.t()
  def library_version, do: :erlang.nif_error(:undef)

  @compile inline: [c_str: 1]
  defp c_str(b) when is_binary(b), do: [b, 0]

  defp c_str(v) do
    raise ArgumentError, "expected a binary, got: #{inspect(v)}"
  end

  @compile {:autoload, false}
  @on_load {:load_nif, 0}

  @doc false
  def load_nif do
    :code.priv_dir(:mlx)
    |> :filename.join(~c"mlx_nif")
    |> :erlang.load_nif(0)
  end
end

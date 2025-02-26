let () = Seq.of_dispenser (fun () -> try Some (read_line ()) with End_of_file -> None)
  |> Seq.map int_of_string
  |> List.of_seq
  |> List.sort compare
  |> List.iter (Printf.printf "%d\n")
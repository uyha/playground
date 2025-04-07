<script lang="ts">
  import Button from "$lib/components/ui/button/button.svelte";
  import Label from "$lib/components/ui/label/label.svelte";
  import Input from "$lib/components/ui/input/input.svelte";

  let props = $props();
  const looping = $state(false);
  const same_wait_time = $state(false);
</script>

<div class="flex flex-col gap-5">
  <div class="flex gap-5">
    <Button disabled={looping}>Start</Button>
    <Button
      disabled={!looping}
      variant="secondary"
      class="text-primary-foreground"
    >
      Stop
    </Button>
  </div>
  <div class="grid grid-cols-[max-content_max-content] gap-5">
    <Label class="my-auto p-2">Status:</Label>
    <p class={["bg-red-800", "justify-self-start", "p-2"]}>
      {looping ? "Looping" : "Not Looping"}
    </p>
    <Label
      class={["my-auto", "p-2", !same_wait_time && "bg-secondary"]}
      for="wait_time"
    >
      Wait Time:
    </Label>
    <Input id="wait_time">60</Input>
  </div>
</div>

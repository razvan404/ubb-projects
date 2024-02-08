export type Item = {
  id?: number;
  name: string;
  takenBy: string | null;
  desiredBy: string[];
  pending?: boolean;
};

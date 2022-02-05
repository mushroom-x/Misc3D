#include <py_misc3d.h>

#include <misc3d/registration/correspondence_matching.h>
#include <misc3d/registration/transform_estimation.h>
#include <misc3d/utils.h>

namespace misc3d {

namespace registration {

void pybind_registration(py::module &m) {
    m.def(
        "compute_transformation_svd",
        [](const PointCloudPtr &src,
           const PointCloudPtr &dst) {
            SVDSolver solver;
            return solver.Solve(*src, *dst);
        },
        "Compute 3D rigid transformation from corresponding point clouds using "
        "SVD",
        py::arg("src"), py::arg("dst"));
    m.def(
        "compute_transformation_teaser",
        [](const PointCloudPtr &src,
           const PointCloudPtr &dst,
           double noise_bound) {
            TeaserSolver solver(noise_bound);
            return solver.Solve(*src, *dst);
        },
        "Compute 3D rigid transformation from corresponding point clouds using "
        "Teaser PlusPlus algorithm",
        py::arg("src"), py::arg("dst"), py::arg("noise_bound") = 0.01);
    m.def(
        "compute_transformation_ransac",
        [](const PointCloudPtr &src,
           const PointCloudPtr &dst,
           const std::pair<std::vector<int>, std::vector<int>> &corres,
           double threshold, int max_iter, double edge_length_threshold) {
            RANSACSolver solver(threshold, max_iter, edge_length_threshold);
            return solver.Solve(*src, *dst, corres);
        },
        "Compute 3D rigid transformation from corresponding point clouds using "
        "RANSAC",
        py::arg("src"), py::arg("dst"), py::arg("corres"),
        py::arg("threshold") = 0.01, py::arg("max_iter") = 100000,
        py::arg("edge_length_threshold") = 0.9);
    m.def(
        "match_correspondence",
        [](const std::shared_ptr<open3d::pipelines::registration::Feature> &src,
           const std::shared_ptr<open3d::pipelines::registration::Feature> &dst,
           bool cross_check) {
            FLANNMatcher matcher(cross_check);
            return matcher.Match(*src, *dst);
        },
        "Match corresponding point clouds using kdtree", py::arg("src"),
        py::arg("dst"), py::arg("cross_check") = true);
}

}  // namespace registration
}  // namespace misc3d
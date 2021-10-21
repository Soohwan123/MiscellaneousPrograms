using Microsoft.EntityFrameworkCore;
using System;
using System.Linq.Expressions;
using System.Collections.Generic;
using System.Diagnostics;
using System.Reflection;
using System.Threading.Tasks;

namespace HelpdeskDAL
{
    public class DepartmentDAO
    {
        readonly IRepository<Department> repo;

        public DepartmentDAO()
        {
            repo = new HelpdeskRepository<Department>();
        }


        public async Task<List<Department>> GetAll()
        {
            return await repo.GetAll();
        }
    }
}
